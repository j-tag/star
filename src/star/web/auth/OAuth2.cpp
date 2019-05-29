#include "includes/star/Star.hpp"

#include <QUrlQuery>
#include <QNetworkReply>

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
                            [=](QNetworkReply *, int) {
        qInfo() << Q_FUNC_INFO << ": Login to Pure account was successful.";
        functor(true, "ورود موفقیت آمیز بود");
        // TODO: Fetch token and refresh token from JSON result and save it
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
    qWarning() << "Username" << strUsername << "password" << strPassword;
    this->login(strUsername, strPassword, [this] (bool result, const QString &strMessage) {
        emit this->loginResult(result, strMessage);
    });
}

void star::web::auth::OAuth2::saveToken(const QString &strToken, const QString &strRefreshToken)
{
    // TODO: Save token and refresh token to be used later
}
