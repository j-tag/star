#include "includes/star/Star.hpp"


star::web::url::UrlManager::UrlManager() {}

star::web::url::UrlManager::~UrlManager() {}

QString star::web::url::UrlManager::getPureUrl() const
{
    return QStringLiteral("https://puresoftware.org/");
}

QString star::web::url::UrlManager::getPureUrl(const QString &strAppend) const
{
    return this->getPureUrl() + strAppend;
}

QString star::web::url::UrlManager::getLoginUrl() const
{
    return this->getPureUrl("user/fa/oauth2/access/token.json");
}
