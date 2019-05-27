#include "includes/star/Star.hpp"

#include <QIODevice>
#include <QNetworkReply>


star::web::WebAccessManager::WebAccessManager():pManager(new QNetworkAccessManager(this)) {

}


star::web::WebAccessManager::~WebAccessManager() {}

void star::web::WebAccessManager::get(const QNetworkRequest &request)
{
    QNetworkReply *reply = this->pManager->get(request);
    QObject::connect(reply, &QNetworkReply::finished,  [=]() {
        qDebug() << reply->error();
        qDebug() << reply->readAll();

    });
    connect(reply, &QNetworkReply::sslErrors,
            [=](){
        qDebug() << "Hi";
    });
}
