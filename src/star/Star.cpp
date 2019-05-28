#include "includes/star/Star.hpp"

#include <QNetworkReply>
#include <QUrlQuery>

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

}

/**
 * @brief Right after starting application, this method will be called.
 */
void star::Star::start()
{
    // Initialize application objects
    this->initObjects();

    QUrlQuery queries;
    queries.addQueryItem("grant_type", "password");
    queries.addQueryItem("username", "hesamgholami@yahoo.com");
    queries.addQueryItem("password", "yourpassword");
    queries.addQueryItem("scope", "star");

    pWebAccessManager->post("https://puresoftware.org/user/en/oauth2/access/token.json", queries, [=](QNetworkReply *reply) {
        qDebug() << reply->error();
        qDebug() << reply->readAll();
    }, "application/x-www-form-urlencoded");
}


/**
 * @brief This method will be initialize member variable of this class.
 */
void star::Star::initObjects()
{
    this->pJalaliDate = new date::CJalaliDate;
    this->pOAuth2 = new web::auth::OAuth2;
    this->pWebAccessManager = new web::WebAccessManager;
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


// Main app object
star::Star s;

