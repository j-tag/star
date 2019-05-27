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

    void get(const QNetworkRequest &request);

private:
    QPointer<QNetworkAccessManager> pManager;
};

}

}

#endif // WEBACCESSMANAGER_HPP
