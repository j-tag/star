#include "includes/star/Star.hpp"

#include <QNetworkReply>
#include <QUrlQuery>


star::web::WebAccessManager::WebAccessManager():pManager(new QNetworkAccessManager(this)) {

}

star::web::WebAccessManager::~WebAccessManager() {}

void star::web::WebAccessManager::get(const QString &strUrl, std::function<void(QNetworkReply *reply)> functor)
{
    QNetworkRequest request(this->generateNormalRequest(strUrl));

    QNetworkReply *reply = this->pManager->get(request);

    connect(reply, &QIODevice::readyRead,  [reply, functor]() {
        functor(reply);
        reply->deleteLater();
    });
}

void star::web::WebAccessManager::post(const QString &strUrl, const QUrlQuery &queries, std::function<void(QNetworkReply *reply)> functor,
                                       const QString &strContentType)
{
    QNetworkRequest request(this->generateNormalRequest(strUrl));

    request.setHeader(QNetworkRequest::ContentTypeHeader, strContentType);

    QNetworkReply *reply = this->pManager->post(request, queries.query(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QIODevice::readyRead, [reply, functor]() {
        functor(reply);
        reply->deleteLater();
    });
}

QNetworkRequest star::web::WebAccessManager::generateNormalRequest(const QString &strUrl)
{
    QNetworkRequest request;

    request.setUrl(QUrl(strUrl));
    request.setRawHeader("User-Agent", "StarApplication 3.0");
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);

    return request;
}
