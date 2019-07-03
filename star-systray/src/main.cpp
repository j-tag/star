#include <QApplication>

#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>
#include <QDebug>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qInfo() << Q_FUNC_INFO << ": Started Star system tray service.";

    // Actions

    auto quitAction = new QAction("&Quit");
    QObject::connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    // Menu
    auto trayIconMenu = new QMenu();
//    trayIconMenu->addAction(minimizeAction);
//    trayIconMenu->addAction(maximizeAction);
//    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    // Make tray icon
    auto trayIcon = new QSystemTrayIcon();
    trayIcon->setContextMenu(trayIconMenu);

    // Tray icon
    trayIcon->setIcon(QIcon(":/images/icon.png"));

    trayIcon->setToolTip("Salam chetori?");

    trayIcon->show();

    trayIcon->showMessage("Oh my God!", "سلام به همه! خوبین شما؟ مراقب خودتون و خوبیاتون و زیباییاتون هستید؟");

    return a.exec();
}
