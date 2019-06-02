#include <functional>
#include "includes/star/Star.hpp"


star::settings::SettingsManager::SettingsManager() {}

star::settings::SettingsManager::~SettingsManager() {}

void star::settings::SettingsManager::setOnlineValue(const QString &strJson)
{
    auto successFunctor = std::bind( &SettingsManager::successOnlineSettingsFunctor,
                                     this, std::placeholders::_1, std::placeholders::_2);

    auto failFunctor = std::bind( &SettingsManager::failedOnlineSettingsFunctor,
                                     this, std::placeholders::_1, std::placeholders::_2);

    s.getWebAccessManager()->withAuthenticationHeader()->post(
                s.getUrlManager()->getPureUrl("apps/fa/star-v3/settings/set.html"),
                strJson, successFunctor, failFunctor);
}

void star::settings::SettingsManager::getOnlineSettings()
{
    auto successFunctor = std::bind( &star::settings::SettingsManager::successOnlineSettingsFunctor,
                                     this, std::placeholders::_1, std::placeholders::_2);

    auto failFunctor = std::bind( &star::settings::SettingsManager::failedOnlineSettingsFunctor,
                                     this, std::placeholders::_1, std::placeholders::_2);

    s.getWebAccessManager()->withAuthenticationHeader()->get(
                s.getUrlManager()->getPureUrl("apps/fa/star-v3/settings/get.html"),
                successFunctor, failFunctor);
}

void star::settings::SettingsManager::setValue(const QString &strKey, const QVariant &value)
{
    this->_settings.setValue(strKey, value);
}

QString star::settings::SettingsManager::getStringValue(const QString &strKey, const QString &strDefaultValue) const
{
    return this->_settings.value(strKey, strDefaultValue).toString();
}

int star::settings::SettingsManager::getIntValue(const QString &strKey, int nDefaultValue)
{
    return this->_settings.value(strKey, nDefaultValue).toInt();
}

void star::settings::SettingsManager::failedOnlineSettingsFunctor(QNetworkReply *reply, int httpStatus)
{
    // Online settings failed to retrive, so we can update with false result

    emit this->onlineSettingsUpdated(false, QString());

    qWarning() << Q_FUNC_INFO << ": Getting online settings failed. HTTP status and result:" <<
                  httpStatus << reply->readAll();
}

void star::settings::SettingsManager::successOnlineSettingsFunctor(QNetworkReply *reply, int httpStatus)
{
    // Online settings retrived successfully, now we can update it in our app
    emit this->onlineSettingsUpdated(true, reply->readAll());
}
