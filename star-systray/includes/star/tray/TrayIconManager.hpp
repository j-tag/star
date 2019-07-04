#ifndef TRAYICONMANAGER_HPP
#define TRAYICONMANAGER_HPP

#include <QObject>
#include <QPointer>
#include <QSystemTrayIcon>

namespace star {

namespace tray {

class TrayIconManager : public QObject
{
    Q_OBJECT
public:
    TrayIconManager();
    virtual ~TrayIconManager();

    void init();
    void showMessage(const QString &strTitle, const QString &strDescription, QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::Information);

private:
    QPointer<QSystemTrayIcon> pSystemTrayIcon;
};

}

}
#endif // TRAYICONMANAGER_HPP
