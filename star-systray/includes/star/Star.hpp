#ifndef STAR_HPP
#define STAR_HPP

/*
 * Logging macroes:
 qDebug() is used for writing custom debug output.
 qInfo() is used for informational messages.
 qWarning() is used to report warnings and recoverable errors in your application.
 qCritical() is used for writing critical error messages and reporting system errors.
 qFatal() is used for writing fatal error messages shortly before exiting.
*/

// Uncomment following macroes to disable output of qDebug(), qInfo() or qWarning()
//#define QT_NO_DEBUG_OUTPUT
//#define QT_NO_INFO_OUTPUT
//#define QT_NO_WARNING_OUTPUT

// Ignore SSL errors [Only for developemnt porpuses]
//#define IGNORE_SSL_ERRORS

#include <QObject>
#include <QDebug>
#include <QPointer>

// Star modules
#include "includes/star/date/CJalaliDate.hpp" // Jalali date handler class
#include "includes/star/web/auth/OAuth2.hpp" // OAuth2 login handler class
#include "includes/star/web/WebAccessManager.hpp" // Web access manager class
#include "includes/star/web/url/UrlManager.hpp" // URL manager class
#include "includes/star/web/auth/ApiToken.hpp" // API Token data model
#include "includes/star/settings/SettingsManager.hpp" // Settings manager class
#include "includes/star/user/UserDetails.hpp" // User details manager class
#include "includes/star/task/TaskManager.hpp" // Task manager class
#include "includes/star/tray/TrayIconManager.hpp" // Tray icon manager class
#include "includes/star/user/BirthdayChecker.hpp" // User birthday checker class
#include "includes/star/server/TcpServer.hpp" // TCP server handler class

namespace star {

class Star : public QObject
{
    Q_OBJECT
public:
    Star();
    virtual ~Star();

    void setJalaliDate(date::CJalaliDate *jalaliDate);
    date::CJalaliDate *getJalaliDate() const;
    void setOAuth2(web::auth::OAuth2 *oAuth2);
    web::auth::OAuth2 *getOAuth2() const;
    void setWebAccessManager(web::WebAccessManager *webAccessManager);
    web::WebAccessManager *getWebAccessManager() const;
    void setUrlManager(web::url::UrlManager *urlManager);
    web::url::UrlManager *getUrlManager() const;
    void setSettingsManager(settings::SettingsManager *settingsManager);
    settings::SettingsManager *getSettingsManager() const;
    void setApiToken(web::auth::ApiToken *apiToken);
    web::auth::ApiToken *getApiToken() const;
    void setUserDetails(user::UserDetails *userDetails);
    user::UserDetails *getUserDetails() const;
    void setTaskManager(task::TaskManager *taskManager);
    task::TaskManager *getTaskManager() const;
    void setTrayIconManager(tray::TrayIconManager *trayIconManager);
    tray::TrayIconManager *getTrayIconManager() const;
    void setBirthdayChecker(user::BirthdayChecker *birthdayChecker);
    user::BirthdayChecker *getBirthdayChecker() const;
    void setTcpServer(server::TcpServer *tcpServer);
    server::TcpServer *getTcpServer() const;

public slots:
    void start();
    void initObjects();
    void end();
    QString getAppVersion() const;
    int getAppVersionNumber();
    void enableAutoStartIfChosen(bool result, QString strMessage);

private:
    void exitIfRanBefore();

private:
    QPointer<date::CJalaliDate> pJalaliDate;
    QPointer<web::auth::OAuth2> pOAuth2;
    QPointer<web::WebAccessManager> pWebAccessManager;
    QPointer<web::url::UrlManager> pUrlManager;
    QPointer<settings::SettingsManager> pSettingsManager;
    QPointer<web::auth::ApiToken> pApiToken;
    QPointer<user::UserDetails> pUserDetails;
    QPointer<task::TaskManager> pTaskManager;
    QPointer<tray::TrayIconManager> pTrayIconManager;
    QPointer<user::BirthdayChecker> pBirthdayChecker;
    QPointer<server::TcpServer> pTcpServer;
};

}

// Main app object
extern star::Star s;

#endif // STAR_HPP
