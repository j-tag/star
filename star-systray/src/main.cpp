#include <QApplication>

#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>
#include <QDebug>
#include <QObject>

#include "includes/star/Star.hpp"

int main(int argc, char *argv[])
{
    // Organization details
    QCoreApplication::setOrganizationName("PureSoft");
    QCoreApplication::setOrganizationDomain("puresoftware.org");
    QCoreApplication::setApplicationName("Star");

    QApplication a(argc, argv);

#ifdef IGNORE_SSL_ERRORS
    // Ignore SSL Errors
    QSslConfiguration sslConf = QSslConfiguration::defaultConfiguration();
    sslConf.setPeerVerifyMode(QSslSocket::VerifyNone);
    QSslConfiguration::setDefaultConfiguration(sslConf);
#endif

    // Initialize application objects
    s.initObjects();

    // Initialize star app
    s.start();

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
