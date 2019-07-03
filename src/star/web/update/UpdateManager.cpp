#include <QJsonDocument>
#include <QJsonObject>

#include "includes/star/Star.hpp"

star::web::update::UpdateManager::UpdateManager() {}

star::web::update::UpdateManager::~UpdateManager() {}

void star::web::update::UpdateManager::check()
{
    QString strPattern("apps/fa/check/star/$VERSION.json");
    auto strUrl = strPattern.replace("$VERSION", QString::number(s.getAppVersionNumber()));

    s.getWebAccessManager()->get(s.getUrlManager()->getPureUrl(strUrl), [=](QNetworkReply *reply, int ) {

        // Read data
        auto jsoc = QJsonDocument::fromJson(reply->readAll());
        auto json = jsoc.object();

        // Is update available ?
        auto isUpdateAvailable = json["is_update_available"].toBool();

        if(isUpdateAvailable) {
            // New version is available
            emit this->updateAvailable();
        }

    });
}
