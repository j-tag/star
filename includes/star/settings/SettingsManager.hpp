#ifndef SETTINGSMANAGER_HPP
#define SETTINGSMANAGER_HPP

#include <QObject>
#include <QSettings>

#include <includes/star/web/auth/ApiToken.hpp>

namespace star {

namespace settings {

class SettingsManager : public QObject
{
    Q_OBJECT
public:
    SettingsManager();
    virtual ~SettingsManager();

    void setValue(const QString &strKey, const QVariant &value);
    QString getStringValue(const QString &strKey, const QString &strDefaultValue = QString()) const;
    int getIntValue(const QString &strKey, int nDefaultValue = 0);

private:
    QSettings _settings;
};

}

}

#endif // SETTINGSMANAGER_HPP
