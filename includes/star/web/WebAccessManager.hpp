#ifndef WEBACCESSMANAGER_HPP
#define WEBACCESSMANAGER_HPP

#include <QObject>
#include <QPointer>
#include <QNetworkAccessManager>

namespace star {

namespace web {

class WebAccessManager : public QObject
{
    Q_OBJECT
public:
    WebAccessManager();
    virtual ~WebAccessManager();


    void get(const QString &strUrl, std::function<void(QNetworkReply *reply)> functor);
    void post(const QString &strUrl, const QUrlQuery &queries, std::function<void(QNetworkReply *reply)> functor,
              const QString &strContentType = QStringLiteral("application/json"));

private:
    QNetworkRequest generateNormalRequest(const QString &strUrl);

private:
    QPointer<QNetworkAccessManager> pManager;
};

}

}

#endif // WEBACCESSMANAGER_HPP
