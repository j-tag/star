#include "includes/star/Star.hpp"

star::Star::Star() {}

star::Star::~Star() {
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
    if(this->pUserDetails) {
        this->pUserDetails->deleteLater();
    }
    if(this->pTaskManager) {
        this->pTaskManager->deleteLater();
    }
}

/**
 * @brief Right after starting application, this method will be called.
 */
void star::Star::start() {
    // Login to Pure account

    auto possibleTokenType = this->pSettingsManager->getStringValue("auth/token/token_type");
    auto possibleAccessToken = this->pSettingsManager->getStringValue("auth/token/access_token");
    auto possibleRefreshToken = this->pSettingsManager->getStringValue("auth/token/refresh_token");
    auto possibleExpiresIn = this->pSettingsManager->getIntValue("auth/token/expires_in");

    // Check to see if we have local token
    if(possibleAccessToken.isNull()) {

        qInfo() << Q_FUNC_INFO << ": No local token found. Showing notif to inform user.";

        // TODO: Show a notification to user to login to app

    } else {

        qInfo() << Q_FUNC_INFO << ": Found local token. Going to use it.";

        // Initialize API token
        this->setApiToken(new web::auth::ApiToken(possibleTokenType, possibleAccessToken, possibleRefreshToken, possibleExpiresIn));

        pWebAccessManager->withAuthenticationHeader()->get(this->getUrlManager()->getPureUrl("apps/fa/star-v3/settings/get.html"),
                                                           [=](QNetworkReply *reply, int ) {
            // Update settings in app
            this->pSettingsManager->setLocalSettings(reply);

            emit s.getOAuth2()->loginResult(true, "");

        }, [=](QNetworkReply *reply, int httpStatus) {
            if(httpStatus == 404) {

                // This user has not any settings yet, so show them a notif to inform them

                // TODO: Show a notification to user to open app and finish the wizard

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

                            // Notify app that user logged in successfully
                            emit s.getOAuth2()->loginResult(true, "");

                        } else {
                            // Failed to use refresh token
                            qInfo() << Q_FUNC_INFO << ": Failed to use refresh token. Possibly expired refresh token:"
                                    << strMessage;

                            // TODO: Show a notification to user to say that we have problems to login to their account
                        }

                    });

                }, [=](QNetworkReply *reply, int httpStatus){

                    if(httpStatus == 404) {

                        // This user has not any settings yet, so tell them to complete the wizard

                        // TODO: Tell the user to complete the result

                    } else if(httpStatus == 401) {

                        qInfo() << Q_FUNC_INFO << ": Tried refresh token and also that was invalid. Now we should inform user.";

                        // TODO: Tell the user to login to their account
                    } else {
                        // Something else is wrong
                        qWarning() << Q_FUNC_INFO << ": Can't get user settings. HTTP Status:" << httpStatus <<
                                      "Result:" << reply->readAll();

                        // TODO: Say:
                        // "نمیتوان تنظیمات شما را از پیورسافت دریافت کرد، لطفاً اتصال اینترنت خود را بررسی کنید و در صورت بر قرار بودن اینترنت لطفاً به پشتیبانی وبسایت پیورسافت اطلاع دهید"
                    }

                });

            } else {
                // Something else is wrong
                qWarning() << Q_FUNC_INFO << ": Can't get user settings. HTTP Status:" << httpStatus <<
                              "Result:" << reply->readAll();

                // TODO: Say:
                // "نمیتوان تنظیمات شما را از پیورسافت دریافت کرد، لطفاً اتصال اینترنت خود را بررسی کنید و در صورت بر قرار بودن اینترنت لطفاً به پشتیبانی وبسایت پیورسافت اطلاع دهید"
            }
        });
    }
}

/**
 * @brief This method will be initialize member variable of this class.
 */
void star::Star::initObjects() {
    this->pJalaliDate = new date::CJalaliDate;
    this->pOAuth2 = new web::auth::OAuth2;
    this->pWebAccessManager = new web::WebAccessManager;
    this->pUrlManager = new web::url::UrlManager;
    this->pSettingsManager = new settings::SettingsManager;
    this->pApiToken = nullptr;
    this->pUserDetails = new user::UserDetails;
    this->pTaskManager = new task::TaskManager;
}

/**
 * @brief Before exiting application, this method will be called.
 */
void star::Star::end() {

}

QString star::Star::getAppVersion() const {
    return VERSION;
}

int star::Star::getAppVersionNumber() {
    return VERSION_NUMBER;
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

void star::Star::setUserDetails(star::user::UserDetails *userDetails)
{
    this->pUserDetails = userDetails;
}

star::user::UserDetails *star::Star::getUserDetails() const
{
    return this->pUserDetails;
}

void star::Star::setTaskManager(star::task::TaskManager *taskManager)
{
    this->pTaskManager = taskManager;
}

star::task::TaskManager *star::Star::getTaskManager() const
{
    return this->pTaskManager;
}

// Main app object
star::Star s;
