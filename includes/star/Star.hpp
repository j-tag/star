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


#include <QObject>
#include <QDebug>
#include <QPointer>

// Star modules
#include "includes/star/date/CJalaliDate.hpp" // Jalali date handler class
#include "includes/star/web/auth/OAuth2.hpp" // OAuth2 login handler class
#include "includes/star/web/WebAccessManager.hpp" // Web access manager class
#include "includes/star/web/url/UrlManager.hpp" // URL manager class
#include "includes/star/web/json/JsonParser.hpp" // JSON parser class
#include "includes/star/web/auth/ApiToken.hpp" // API Token data model

namespace star {

class Star : public QObject
{
    Q_OBJECT
public:
    explicit Star(QObject *parent = nullptr);
    ~Star();

    void setJalaliDate(date::CJalaliDate *jalaliDate);
    date::CJalaliDate *getJalaliDate() const;
    void setOAuth2(web::auth::OAuth2 *oAuth2);
    web::auth::OAuth2 *getOAuth2() const;
    void setWebAccessManager(web::WebAccessManager *webAccessManager);
    web::WebAccessManager *getWebAccessManager() const;
    void setUrlManager(web::url::UrlManager *urlManager);
    web::url::UrlManager *getUrlManager() const;
    void setJsonParser(web::json::JsonParser *jsonParser);
    web::json::JsonParser *getJsonParser() const;


signals:

public slots:
    void start();
    void initObjects();
    void end();

protected:
    QPointer<date::CJalaliDate> pJalaliDate;
    QPointer<web::auth::OAuth2> pOAuth2;
    QPointer<web::WebAccessManager> pWebAccessManager;
    QPointer<web::url::UrlManager> pUrlManager;
    QPointer<web::json::JsonParser> pJsonParser;
};

}


// Main app object
extern star::Star s;

#endif // STAR_HPP
