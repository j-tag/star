#ifndef OAUTH2_HPP
#define OAUTH2_HPP

#include "ApiToken.hpp"

#include <functional>

#include <QObject>

namespace star {

namespace web {

namespace auth {

class OAuth2 : public QObject
{
    Q_OBJECT
public:

    explicit OAuth2(QObject *parent = nullptr);

    void login(const QString &strUsername, const QString &strPassword, std::function<void(bool result, const QString &strMessage)> functor);

signals:
    void loginResult(bool result, QString strMessage);

public slots:
    void login(const QString &strUsername, const QString &strPassword);

private:
    void saveToken(ApiToken *apiToken);
};

}

}

}


#endif // OAUTH2_HPP
