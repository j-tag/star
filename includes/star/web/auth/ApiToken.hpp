#ifndef APITOKEN_HPP
#define APITOKEN_HPP

#include <QObject>

namespace star {

namespace web {

namespace auth {

class ApiToken : public QObject
{
    Q_OBJECT
public:
    ApiToken(const QString &strTokenType, const QString &strAccessToken, const QString &strRefreshToken, int nExpiresIn)
        : _strTokenType(strTokenType), _strAccessToken(strAccessToken), _strRefreshToken(strRefreshToken), _nExpiresIn(nExpiresIn) {}

    virtual ~ApiToken() {}

    QString getTokenType() const { return this->_strTokenType; }
    QString getAccessToken() const { return this->_strAccessToken; }
    QString getRefreshToken() const { return this->_strRefreshToken; }
    int getExpiresin() const { return this->_nExpiresIn; }

private:
    QString _strTokenType;
    QString _strAccessToken;
    QString _strRefreshToken;
    int _nExpiresIn;
};

}

}

}

#endif // APITOKEN_HPP
