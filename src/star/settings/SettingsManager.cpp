#include "includes/star/Star.hpp"

star::settings::SettingsManager::SettingsManager() {}

star::settings::SettingsManager::~SettingsManager() {}

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
