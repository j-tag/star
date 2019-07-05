#include <QApplication>

#include "includes/star/Star.hpp"

int main(int argc, char *argv[])
{
    // Organization details
    QCoreApplication::setOrganizationName("PureSoft");
    QCoreApplication::setOrganizationDomain("puresoftware.org");
    QCoreApplication::setApplicationName("Star");

    QApplication a(argc, argv);

    QObject::connect(&a, &QCoreApplication::aboutToQuit, [] {

        qInfo() << Q_FUNC_INFO << ": Cleaning up systray runtime settings.";

        QSettings settings("PureSoft", "Star");
        settings.remove("app/tray/runtime");
    });

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

    return a.exec();
}
