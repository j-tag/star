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
                            [=](QNetworkReply *reply, int) {

        qInfo() << Q_FUNC_INFO << ": Login to Pure account was successful.";

        functor(true, "ورود موفقیت آمیز بود");

        // Now fetch token and refresh token from JSON result and save it

        auto jsoc = QJsonDocument::fromJson(reply->readAll());

        if(jsoc.isNull()) {
            // JSON result was invalid
            functor(false, "پاسخ دریافت شده از پیورسافت معتبر نیست");
            return;
        }

        auto json = jsoc.object();

        auto tokenType = s.getJsonParser()->getSafeStringValue(json, "token_type");

        auto accessToken = s.getJsonParser()->getSafeStringValue(json, "access_token");

        auto refreshToken = s.getJsonParser()->getSafeStringValue(json, "refresh_token");

        auto expiresIn = s.getJsonParser()->getSafeIntegerValue(json, "expires_in");

        ApiToken *apiToken = new ApiToken(tokenType, accessToken, refreshToken, expiresIn);

        this->saveToken(apiToken);

    },
    [=](QNetworkReply *reply, int status) {

        qWarning() << Q_FUNC_INFO << ": Login to Pure account were failed.";
        qWarning() << status;

        if(reply->error() == QNetworkReply::NoError) {
            functor(false, "نام کاربری و گذرواژه با یکدیگر مطابقت ندارند");
        } else {
            functor(false, "خطا در هنگام ورود به حساب کاربری، لطفاً اتصال اینترنت را بررسی کنید");
        }

    },
    "application/x-www-form-urlencoded");
}

void star::web::auth::OAuth2::login(const QString &strUsername, const QString &strPassword)
{
    this->login(strUsername, strPassword, [this] (bool result, const QString &strMessage) {
        emit this->loginResult(result, strMessage);
    });
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
