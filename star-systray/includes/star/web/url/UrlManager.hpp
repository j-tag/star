#ifndef URLMANAGER_HPP
#define URLMANAGER_HPP

#include <QObject>

namespace star {

namespace web {

namespace url {

class UrlManager : public QObject
{
    Q_OBJECT
public:
    UrlManager();
    virtual ~UrlManager();

    QString getPureUrl() const;
    QString getPureUrl(const QString &strAppend) const;
    QString getLoginUrl() const;
};

}

}

}


#endif // URLMANAGER_HPP
