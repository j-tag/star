#include "includes/star/Star.hpp"

#include <QUrlQuery>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

star::web::auth::OAuth2::OAuth2(QObject *parent) : QObject(parent)
{

}

void star::web::auth::OAuth2::login(const QString &strUsername, const QString &strPassword, std::function<void (bool, const QString &)> functor)
{
    QUrlQuery queries;

    queries.addQueryItem("grant_type", "password");
    queries.addQueryItem("username", strUsername);
    queries.addQueryItem("password", strPassword);
    queries.addQueryItem("scope", "star");

    s.getWebAccessManager()->post(s.getUrlManager()->getLoginUrl(), queries,
                            [=](QNetworkReply *reply, int httpStatus) {

        this->tokenResultHandler(reply, httpStatus, functor);
    },
    [=](QNetworkReply *reply, int status) {

        qWarning() << Q_FUNC_INFO << ": Login to Pure account were failed. HTTP Status:" << status;

        if(reply->error() == QNetworkReply::NoError) {
            functor(false, "نام کاربری و گذرواژه با یکدیگر مطابقت ندارند");
        } else {
            functor(false, "خطا در هنگام ورود به حساب کاربری، لطفاً اتصال اینترنت را بررسی کنید");
        }

    },
    "application/x-www-form-urlencoded");
}

void star::web::auth::OAuth2::regenerateAccessToken(const QString &strRefreshToken, std::function<void (QNetworkReply *, int)> functor, std::function<void (QNetworkReply *, int)> failFunctor)
{
    QUrlQuery queries;

    queries.addQueryItem("grant_type", "refresh_token");
    queries.addQueryItem("refresh_token", strRefreshToken);

    s.getWebAccessManager()->post(s.getUrlManager()->getLoginUrl(), queries, functor, failFunctor);
}

void star::web::auth::OAuth2::login(const QString &strUsername, const QString &strPassword)
{
    this->login(strUsername, strPassword, [=] (bool result, const QString &strMessage) {
        emit this->loginResult(result, strMessage);
    });
}

void star::web::auth::OAuth2::logout()
{
    s.getSettingsManager()->removeValue("auth/token/token_type");
    s.getSettingsManager()->removeValue("auth/token/access_token");
    s.getSettingsManager()->removeValue("auth/token/refresh_token");
    s.getSettingsManager()->removeValue("auth/token/expires_in");
}

void star::web::auth::OAuth2::tokenResultHandler(QNetworkReply *reply, int , std::function<void(bool, const QString &)> functor)
{

    // Now fetch token and refresh token from JSON result and save it

    auto jsoc = QJsonDocument::fromJson(reply->readAll());

    if(jsoc.isNull()) {
        // JSON result was invalid
        functor(false, "پاسخ دریافت شده از پیورسافت معتبر نیست");
        return;
    }

    qInfo() << Q_FUNC_INFO << ": Login to Pure account was successful.";

    auto json = jsoc.object();

    auto tokenType = json["token_type"].toString();
    auto accessToken = json["access_token"].toString();
    auto refreshToken = json["refresh_token"].toString();
    auto expiresIn = json["expires_in"].toInt(-1);

    ApiToken *apiToken = new ApiToken(tokenType, accessToken, refreshToken, expiresIn);

    this->saveToken(apiToken);

    functor(true, "ورود موفقیت آمیز بود");
}

void star::web::auth::OAuth2::saveToken(star::web::auth::ApiToken *apiToken)
{
    // Save token data to be used later

    s.getSettingsManager()->setValue("auth/token/token_type", apiToken->getTokenType());
    s.getSettingsManager()->setValue("auth/token/access_token", apiToken->getAccessToken());
    s.getSettingsManager()->setValue("auth/token/refresh_token", apiToken->getRefreshToken());
    s.getSettingsManager()->setValue("auth/token/expires_in", apiToken->getExpiresIn());

    s.setApiToken(apiToken);
}
