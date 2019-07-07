#include <QApplication>

#include "includes/star/Star.hpp"

int main(int argc, char *argv[])
{
    // Organization details
    QCoreApplication::setOrganizationName("PureSoft");
    QCoreApplication::setOrganizationDomain("puresoftware.org");
    QCoreApplication::setApplicationName("Star");

    QApplication a(argc, argv);

    QObject::connect(&a, &QCoreApplication::aboutToQuit, [=] {

        qInfo() << Q_FUNC_INFO << ": Quiting Star systray application...";

        qInfo() << Q_FUNC_INFO << ": Closing up all TCP clients.";

        s.getTcpServer()->closeAllClients();
        s.getTcpServer()->close();

    });

#ifdef IGNORE_SSL_ERRORS
    // Ignore SSL Errors
    QSslConfiguration sslConf = QSslConfiguration::defaultConfiguration();
    sslConf.setPeerVerifyMode(QSslSocket::VerifyNone);
    QSslConfiguration::setDefaultConfiguration(sslConf);
#endif

    // Initialize application objects
    s.initObjects();

    // Initialize star systray app
    s.start();

    qInfo() << Q_FUNC_INFO << ": Started Star system tray service.";

    return a.exec();
}
