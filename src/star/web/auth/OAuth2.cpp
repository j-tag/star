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

    s.getWebAccessManager()->post("https://puresoftware.org/user/en/oauth2/access/token.json", queries,
                            [=](QNetworkReply *, int) {
        qInfo() << Q_FUNC_INFO << ": Login to Pure account was successful.";
        functor(true, "ورود موفقیت آمیز بود");
    },
    [=](QNetworkReply *reply, int) {

        qWarning() << Q_FUNC_INFO << ": Login to Pure account were failed.";

        if(reply->error() == QNetworkReply::NoError) {
            functor(false, "نام کاربری و گذرواژه با یکدیگر مطابقت ندارند");
        } else {
            functor(false, "خطا در هنگام ورود به حساب کاربری، لطفاً اتصال اینترنت را بررسی کنید");
        }

    },
    "application/x-www-form-urlencoded");
}
