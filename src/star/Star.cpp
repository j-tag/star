#include "includes/star/Star.hpp"

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>

star::Star::Star(QObject *parent) : QObject(parent)
{

}

star::Star::~Star()
{
    // Free up member objects
    if(this->pJalaliDate) {
        this->pJalaliDate->deleteLater();
    }
    if(this->pOAuth2) {
        this->pOAuth2->deleteLater();
    }
    if(this->pWebAccessManager) {
        this->pWebAccessManager->deleteLater();
    }
    if(this->pUrlManager) {
        this->pUrlManager->deleteLater();
    }
    if(this->pSettingsManager) {
        this->pSettingsManager->deleteLater();
    }
    if(this->pApiToken) {
        this->pApiToken->deleteLater();
    }
    if(this->pUiUserDetails) {
        this->pUiUserDetails->deleteLater();
    }
    if(this->pUiAlerts) {
        this->pUiAlerts->deleteLater();
    }
    if(this->pUiSetupWizard) {
        this->pUiSetupWizard->deleteLater();
    }
    if(this->pHijriDate) {
        this->pHijriDate->deleteLater();
    }
    if(this->pTodayEvents) {
        this->pTodayEvents->deleteLater();
    }

}

/**
 * @brief Right after starting application, this method will be called.
 */
void star::Star::start()
{
    // Login to Pure account

    auto possibleTokenType = this->pSettingsManager->getStringValue("auth/token/token_type");
    auto possibleAccessToken = this->pSettingsManager->getStringValue("auth/token/access_token");
    auto possibleRefreshToken = this->pSettingsManager->getStringValue("auth/token/refresh_token");
    auto possibleExpiresIn = this->pSettingsManager->getIntValue("auth/token/expires_in");

    // Check to see if we have local token
    if(possibleAccessToken.isNull()) {

        qInfo() << Q_FUNC_INFO << ": No local token found. Showing login form.";

        // We don't have any token stored, so show login box
        emit s.getOAuth2()->showLoginBox(true);

    } else {

        qInfo() << Q_FUNC_INFO << ": Found local token. Going to use it.";

        // Initialize API token
        this->setApiToken(new web::auth::ApiToken(possibleTokenType, possibleAccessToken, possibleRefreshToken, possibleExpiresIn));

        pWebAccessManager->withAuthenticationHeader()->get(this->getUrlManager()->getPureUrl("apps/fa/star-v3/settings/get.html"),
                                                           [=](QNetworkReply *reply, int ) {
            // Update settings in app
            this->pSettingsManager->setLocalSettings(reply);

            emit s.getOAuth2()->loginResult(true, "");

            // Close all login related boxes
            emit s.getOAuth2()->showLoginBox(false);

        }, [=](QNetworkReply *reply, int httpStatus) {
            if(httpStatus == 404) {

                // This user has not any settings yet, so show them setup wizard to begin
                emit this->pUiSetupWizard->initSetupWizard();

                // Close all login related boxes
                emit s.getOAuth2()->showLoginBox(false);

            } else if(httpStatus == 401) {

                // Token is expired, so try refresh token
                qInfo() << Q_FUNC_INFO << ": Possibly expired access token. HTTP Status:" << httpStatus <<
                              "Result:" << reply->readAll();
                qInfo() << Q_FUNC_INFO << ": Now trying to use refresh token...";

                // Using refresh token
                this->pOAuth2->regenerateAccessToken(possibleRefreshToken,
                                       [=](QNetworkReply *reply, int httpStatus) {


                    s.getOAuth2()->tokenResultHandler(reply, httpStatus, [=] (bool result, const QString &strMessage) {

                        if(result) {
                            // Using refresh token was successful
                            qInfo() << Q_FUNC_INFO << ": Successfully logged in using refresh token.";

                            // Reload settings in app
                            this->pSettingsManager->getOnlineSettings();

                            // Close all login related boxes
                            emit s.getOAuth2()->showLoginBox(false);
                        } else {
                            // Failed to use refresh token
                            qInfo() << Q_FUNC_INFO << ": Failed to use refresh token. Possibly expired refresh token:"
                                    << strMessage;

                            // Because we have failed using refresh token, finally we should show login box to user
                            emit s.getOAuth2()->showLoginBox(true);
                        }

                    });

                }, [=](QNetworkReply *reply, int httpStatus){


                    if(httpStatus == 404) {

                        // This user has not any settings yet, so show them setup wizard to begin
                        emit this->pUiSetupWizard->initSetupWizard();

                        // Close all login related boxes
                        emit s.getOAuth2()->showLoginBox(false);

                    } else if(httpStatus == 401) {

                        qInfo() << Q_FUNC_INFO << ": Tried refresh token and also that was invalid. Now we should show login box.";

                        // Refresh token is also expired, so show login box here
                        emit s.getOAuth2()->showLoginBox(true);
                    } else {
                        // Something else is wrong
                        qWarning() << Q_FUNC_INFO << ": Can't get user settings. HTTP Status:" << httpStatus <<
                                      "Result:" << reply->readAll();

                        s.getUiAlerts()->showErrorMessage("نمیتوان تنظیمات شما را از پیورسافت دریافت کرد، لطفاً اتصال اینترنت خود را بررسی کنید و در صورت بر قرار بودن اینترنت لطفاً به پشتیبانی وبسایت پیورسافت اطلاع دهید");
                    }

                });

            } else {
                // Something else is wrong
                qWarning() << Q_FUNC_INFO << ": Can't get user settings. HTTP Status:" << httpStatus <<
                              "Result:" << reply->readAll();

                s.getUiAlerts()->showErrorMessage("نمیتوان تنظیمات شما را از پیورسافت دریافت کرد، لطفاً اتصال اینترنت خود را بررسی کنید و در صورت بر قرار بودن اینترنت لطفاً به پشتیبانی وبسایت پیورسافت اطلاع دهید");
            }
        });
    }

}


/**
 * @brief This method will be initialize member variable of this class.
 */
void star::Star::initObjects()
{
    this->pJalaliDate = new date::CJalaliDate;
    this->pOAuth2 = new web::auth::OAuth2;
    this->pWebAccessManager = new web::WebAccessManager;
    this->pUrlManager = new web::url::UrlManager;
    this->pSettingsManager = new settings::SettingsManager;
    this->pApiToken = nullptr;
    this->pUiUserDetails = new ui::home::UserDetails;
    this->pUiAlerts = new ui::general::Alerts;
    this->pUiSetupWizard = new ui::setup::SetupWizard;
    this->pHijriDate = new date::HijriDateCalculator;
    this->pTodayEvents = new date::events::TodayEvents;
}

/**
 * @brief Before exiting application, this method will be called.
 */
void star::Star::end()
{

}

void star::Star::setJalaliDate(date::CJalaliDate *jalaliDate)
{
    this->pJalaliDate = jalaliDate;
}

star::date::CJalaliDate *star::Star::getJalaliDate() const
{
    return this->pJalaliDate;
}

void star::Star::setOAuth2(web::auth::OAuth2 *oAuth2)
{
    this->pOAuth2 = oAuth2;
}

star::web::auth::OAuth2 *star::Star::getOAuth2() const
{
    return this->pOAuth2;
}

void star::Star::setWebAccessManager(star::web::WebAccessManager *webAccessManager)
{
    this->pWebAccessManager = webAccessManager;
}

star::web::WebAccessManager *star::Star::getWebAccessManager() const
{
    return this->pWebAccessManager;
}

void star::Star::setUrlManager(star::web::url::UrlManager *urlManager)
{
    this->pUrlManager = urlManager;
}

star::web::url::UrlManager *star::Star::getUrlManager() const
{
    return this->pUrlManager;
}

void star::Star::setSettingsManager(star::settings::SettingsManager *settingsManager)
{
    this->pSettingsManager = settingsManager;
}

star::settings::SettingsManager *star::Star::getSettingsManager() const
{
    return this->pSettingsManager;
}

void star::Star::setApiToken(star::web::auth::ApiToken *apiToken)
{
    this->pApiToken = apiToken;
}

star::web::auth::ApiToken *star::Star::getApiToken() const
{
    return this->pApiToken;
}

void star::Star::setUiUserDetails(star::ui::home::UserDetails *userDetails)
{
    this->pUiUserDetails = userDetails;
}

star::ui::home::UserDetails *star::Star::getUiUserDetails() const
{
    return this->pUiUserDetails;
}

void star::Star::setUiAlerts(star::ui::general::Alerts *alerts)
{
    this->pUiAlerts = alerts;
}

star::ui::general::Alerts *star::Star::getUiAlerts() const
{
    return this->pUiAlerts;
}

void star::Star::setUiSetupWizard(star::ui::setup::SetupWizard *setupWizard)
{
    this->pUiSetupWizard = setupWizard;
}

star::ui::setup::SetupWizard *star::Star::getUiSetupWizard() const
{
    return this->pUiSetupWizard;
}

void star::Star::setHijriDate(star::date::HijriDateCalculator *hijriDate)
{
    this->pHijriDate = hijriDate;
}

star::date::HijriDateCalculator *star::Star::getHijriDate() const
{
    return this->pHijriDate;
}

void star::Star::setTodayEvents(star::date::events::TodayEvents *todayEvents)
{
    this->pTodayEvents = todayEvents;
}

star::date::events::TodayEvents *star::Star::getTodayEvents() const
{
    return this->pTodayEvents;
}


// Main app object
star::Star s;

