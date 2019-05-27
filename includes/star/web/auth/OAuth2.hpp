#ifndef OAUTH2_HPP
#define OAUTH2_HPP

#include <QObject>

namespace star {

namespace web {

namespace auth {

class OAuth2 : public QObject
{
    Q_OBJECT
public:
    explicit OAuth2(QObject *parent = nullptr);

    bool login(const QString &strUsername, const QString &strPassword);

signals:

public slots:
};

}

}

}


#endif // OAUTH2_HPP
