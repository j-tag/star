#include "includes/star/Star.hpp"

#include <QCoreApplication>
#include <QTimer>

star::Star::Star():bIsLoggedIn(false) {}

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
    if(this->pTrayIconManager) {
        this->pTrayIconManager->deleteLater();
    }
    if(this->pBirthdayChecker) {
        this->pBirthdayChecker->deleteLater();
    }
    if(this->pTcpServer) {
        this->pTcpServer->deleteLater();
    }
    if(this->pTcpClient) {
        this->pTcpClient->deleteLater();
    }
}

/**
 * @brief Right after starting application, this method will be called.
 */
void star::Star::start() {

    // Exit if ran before
    this->exitIfRanBefore();
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
    this->pTrayIconManager = new tray::TrayIconManager;
    this->pBirthdayChecker = new user::BirthdayChecker;
    this->pTcpServer = new server::TcpServer;
    this->pTcpClient = new client::TcpClient;
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

void star::Star::enableAutoStartIfChosen(bool result, QString )
{
    this->bIsLoggedIn = result;

    if(result == true) {

        QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",
                             QSettings::NativeFormat);

        if(s.getUserDetails()->getAutoStart() == true) {
            settings.setValue("StarSysTray",
                               QCoreApplication::applicationFilePath().replace('/', '\\').prepend('"').append('"'));
        } else {
            settings.remove("StarSysTray");
        }
    }

}

void star::Star::mainStart()
{
    // Init local TCP server
    this->pTcpServer->initServer();

    // Init tray icon
    this->getTrayIconManager()->init();

    // Check auto start
    connect(s.getOAuth2(), &star::web::auth::OAuth2::loginResult, this, &Star::enableAutoStartIfChosen);

    // Login to Pure account
    this->login();

    // Initialize login checker
    this->initLoginChecker();
}

void star::Star::login()
{
    // Login to Pure account

    auto possibleTokenType = this->pSettingsManager->getStringValue("auth/token/token_type");
    auto possibleAccessToken = this->pSettingsManager->getStringValue("auth/token/access_token");
    auto possibleRefreshToken = this->pSettingsManager->getStringValue("auth/token/refresh_token");
    auto possibleExpiresIn = this->pSettingsManager->getIntValue("auth/token/expires_in");

    // Check to see if we have local token
    if(possibleAccessToken.isNull()) {

        qInfo() << Q_FUNC_INFO << ": No local token found. Showing notif to inform user.";

        // Show a notification to user to login to app
        this->getTrayIconManager()->showMessage("ورود به ستاره",
                                                "لطفاً با کلیک بر روی این آیکن نرم افزار ستاره را اجرا کرده و وارد حساب کاربری خود در پیورسافت شوید تا بتوانید به راحتی از ستاره استفاده کنید",
                                                QSystemTrayIcon::Warning);

    } else {

        qInfo() << Q_FUNC_INFO << ": Found local token. Going to use it.";

        // Initialize API token
        this->setApiToken(new web::auth::ApiToken(possibleTokenType, possibleAccessToken, possibleRefreshToken, possibleExpiresIn));

        pWebAccessManager->withAuthenticationHeader()->get(this->getUrlManager()->getPureUrl("apps/fa/star-v4/settings/get.html"),
                                                           [=](QNetworkReply *reply, int ) {
            // Update settings in app
            this->pSettingsManager->setLocalSettings(reply);

            emit s.getOAuth2()->loginResult(true, "");

        }, [=](QNetworkReply *reply, int httpStatus) {
            if(httpStatus == 404) {

                // This user has not any settings yet, so show them a notif to inform them

                // Show a notification to user to open app and finish the wizard
                this->getTrayIconManager()->showMessage("تکمیل پروفایل کاربری",
                                                        "لطفاً با کلیک بر روی این آیکن نرم افزار ستاره را اجرا کرده و پروفایل خود را تکمیل کنید تا بتوانید به راحتی از ستاره استفاده کنید",
                                                        QSystemTrayIcon::Warning);

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

                            // Show a notification to user to say that we have problems to login to their account
                            this->getTrayIconManager()->showMessage("ورود به ستاره",
                                                                    "متأسفانه نتوانستیم وارد حساب کاربری شما در پیورسافت شویم، برای اینکه رویدادهای تقویم در ستاره همگام سازی شوند، شما باید با کلیک برروی اینجا وارد حساب کاربری خود در پیورسافت شوید",
                                                                    QSystemTrayIcon::Warning);
                        }

                    });

                }, [=](QNetworkReply *reply, int httpStatus){

                    if(httpStatus == 401) {

                        qInfo() << Q_FUNC_INFO << ": Tried refresh token and also that was invalid. Now we should inform user.";

                        // Tell the user to login to their account
                        this->getTrayIconManager()->showMessage("ورود به ستاره",
                                                                "متأسفانه نتوانستیم وارد حساب کاربری شما در پیورسافت شویم، برای اینکه رویدادهای تقویم در ستاره همگام سازی شوند، شما باید با کلیک برروی اینجا وارد حساب کاربری خود در پیورسافت شوید",
                                                                QSystemTrayIcon::Warning);
                    } else {
                        // Something else is wrong
                        qWarning() << Q_FUNC_INFO << ": Can't get user settings. HTTP Status:" << httpStatus <<
                                      "Result:" << reply->readAll();

                        this->getTrayIconManager()->showMessage("ورود به ستاره",
                                                               "نمیتوان تنظیمات شما را از پیورسافت دریافت کرد، لطفاً اتصال اینترنت خود را بررسی کنید و در صورت بر قرار بودن اینترنت لطفاً به پشتیبانی وبسایت پیورسافت اطلاع دهید",
                                                                QSystemTrayIcon::Warning);

                    }

                });

            } else {
                // Something else is wrong
                qWarning() << Q_FUNC_INFO << ": Can't get user settings. HTTP Status:" << httpStatus <<
                              "Result:" << reply->readAll();

                this->getTrayIconManager()->showMessage("ورود به ستاره",
                                                       "نمیتوان تنظیمات شما را از پیورسافت دریافت کرد، لطفاً اتصال اینترنت خود را بررسی کنید و در صورت بر قرار بودن اینترنت لطفاً به پشتیبانی وبسایت پیورسافت اطلاع دهید",
                                                        QSystemTrayIcon::Warning);
            }
        });
    }
}

void star::Star::exitIfRanBefore()
{
    this->pTcpClient->connectToServer([this]() {
        // Connected to TCP socker server, so there is another instance listening before us, so don't start app
        qWarning() << Q_FUNC_INFO << ": Application re-run detected. Quiting...";

        this->pTcpClient->close();
        qApp->quit();
        exit(0);
    },
    [this]() {
        // Failed to connect to TCP server, therefore there was no inctance before us, so we can keep going
        this->mainStart();
    });
}

void star::Star::initLoginChecker()
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Star::checkLoginStatus));
    timer->start(5 * 60 * 1000); // 5 Min
}

void star::Star::checkLoginStatus()
{
    qInfo() << Q_FUNC_INFO << ": Checking up login status...";

    if(this->bIsLoggedIn) {
        // User is logged in
        qInfo() << Q_FUNC_INFO << ": User is logged in. No action needed.";
    } else {
        // User is not logged in, try to login again
        qWarning() << Q_FUNC_INFO << ": User is not logged in. Trying to login...";
        this->login();
    }
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

void star::Star::setTrayIconManager(star::tray::TrayIconManager *trayIconManager)
{
    this->pTrayIconManager = trayIconManager;
}

star::tray::TrayIconManager *star::Star::getTrayIconManager() const
{
    return this->pTrayIconManager;
}

void star::Star::setBirthdayChecker(star::user::BirthdayChecker *birthdayChecker)
{
    this->pBirthdayChecker = birthdayChecker;
}

star::user::BirthdayChecker *star::Star::getBirthdayChecker() const
{
    return this->pBirthdayChecker;
}

void star::Star::setTcpServer(star::server::TcpServer *tcpServer)
{
    this->pTcpServer = tcpServer;
}

star::server::TcpServer *star::Star::getTcpServer() const
{
    return this->pTcpServer;
}

void star::Star::setTcpClient(star::client::TcpClient *tcpClient)
{
    this->pTcpClient = tcpClient;
}

star::client::TcpClient *star::Star::getTcpClient() const
{
    return this->pTcpClient;
}

// Main app object
star::Star s;
