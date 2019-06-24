#include "includes/star/Star.hpp"

#include <QNetworkReply>
#include <QUrlQuery>


star::web::WebAccessManager::WebAccessManager():pManager(new QNetworkAccessManager(this)) {

}

star::web::WebAccessManager::~WebAccessManager() {}

star::web::WebAccessManager *star::web::WebAccessManager::withAuthenticationHeader()
{
    auto apiToken = s.getApiToken();

    if(apiToken == nullptr) {
        qCritical() << Q_FUNC_INFO << "No API token found, but a request with authentication header made.";
    }

    this->hashHeaders["Authorization"] = "Bearer " + apiToken->getAccessToken();

    return this;
}

void star::web::WebAccessManager::get(const QString &strUrl, std::function<void(QNetworkReply *reply, int httpStatus)> functor,
                                      std::function<void(QNetworkReply *reply, int httpStatus)> failFunctor)
{
    qDebug() << "HTTP request: GET:" << strUrl;

    QNetworkRequest request(this->generateNormalRequest(strUrl));

    this->setHeaders(request);

    QNetworkReply *reply = this->pManager->get(request);

    connect(reply, &QIODevice::readyRead,  [reply, functor, failFunctor]() {

        int httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        if(reply->error() == QNetworkReply::NoError && httpStatusCode >= 200 && httpStatusCode < 300) {
            functor(reply, httpStatusCode);
        } else {
            failFunctor(reply, httpStatusCode);
        }

        reply->deleteLater();
    });
}

void star::web::WebAccessManager::post(const QString &strUrl, const QUrlQuery &queries, std::function<void(QNetworkReply *reply, int httpStatus)> functor,
                                       std::function<void(QNetworkReply *reply, int httpStatus)> failFunctor,
                                       const QString &strContentType)
{
    qDebug() << "HTTP request: POST:" << strUrl;

    QNetworkRequest request(this->generateNormalRequest(strUrl));

    this->setHeaders(request);

    request.setHeader(QNetworkRequest::ContentTypeHeader, strContentType);

    QNetworkReply *reply = this->pManager->post(request, queries.query(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QIODevice::readyRead, [reply, functor, failFunctor]() {

        int httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        if(reply->error() == QNetworkReply::NoError && httpStatusCode >= 200 && httpStatusCode < 300) {
            functor(reply, httpStatusCode);
        } else {
            failFunctor(reply, httpStatusCode);
        }

        reply->deleteLater();
    });
}

void star::web::WebAccessManager::post(const QString &strUrl, const QString &strBody, std::function<void (QNetworkReply *, int)> functor, std::function<void (QNetworkReply *, int)> failFunctor, const QString &strContentType)
{
    qDebug() << "HTTP request: POST:" << strUrl;

    QNetworkRequest request(this->generateNormalRequest(strUrl));

    this->setHeaders(request);

    request.setHeader(QNetworkRequest::ContentTypeHeader, strContentType);

    QNetworkReply *reply = this->pManager->post(request, strBody.toUtf8());

    connect(reply, &QIODevice::readyRead, [reply, functor, failFunctor]() {

        int httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        if(reply->error() == QNetworkReply::NoError && httpStatusCode >= 200 && httpStatusCode < 300) {
            functor(reply, httpStatusCode);
        } else {
            failFunctor(reply, httpStatusCode);
        }

        reply->deleteLater();
    });
}

QNetworkRequest star::web::WebAccessManager::generateNormalRequest(const QString &strUrl)
{
    QNetworkRequest request;

    request.setUrl(QUrl(strUrl));
    request.setRawHeader("User-Agent", "StarDesktopApplication 3.0");
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);

    return request;
}

QNetworkRequest &star::web::WebAccessManager::setHeaders(QNetworkRequest &request)
{
    QHashIterator<QString, QString> i(this->hashHeaders);

    while (i.hasNext()) {
        i.next();
        request.setRawHeader(i.key().toUtf8(), i.value().toUtf8());
    }

    return request;
}
