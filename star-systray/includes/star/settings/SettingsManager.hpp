#ifndef SETTINGSMANAGER_HPP
#define SETTINGSMANAGER_HPP

#include <QNetworkReply>
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

    void setLocalSettings(QNetworkReply *reply);

signals:
    void onlineSettingsUpdated(bool result, QString newSettings);

public slots:

    void setOnlineValue(const QString &strJson);
    void getOnlineSettings();

    void setValue(const QString &strKey, const QVariant &value);
    QString getStringValue(const QString &strKey, const QString &strDefaultValue = QString()) const;
    int getIntValue(const QString &strKey, int nDefaultValue = 0);
    qint64 getQint64Value(const QString &strKey, qint64 nDefaultValue = 0);
    void removeValue(const QString &strKey);

private:

    void successOnlineSettingsFunctor(QNetworkReply *reply, int);
    void failedOnlineSettingsFunctor(QNetworkReply *reply, int httpStatus);

private:
    QSettings _settings;
};

}

}

#endif // SETTINGSMANAGER_HPP
