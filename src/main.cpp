#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QQmlContext>
#include <QFont>

// C++ Modules
#include "includes/star/Star.hpp"



int main(int argc, char *argv[])
{
    // Organization details
    QCoreApplication::setOrganizationName("PureSoft");
    QCoreApplication::setOrganizationDomain("puresoftware.org");
    QCoreApplication::setApplicationName("Star");

    QApplication app(argc, argv);

    // Set application font
    QFont tFont;
    tFont.setFamily("IRANSans");
    app.setFont(tFont);

    // Make QML engine
    QQmlApplicationEngine engine;

    // Load C++ side, modules
    s.start();

    // Star main object
    engine.rootContext()->setContextProperty("star", &s);

    // Jalali date handler
    engine.rootContext()->setContextProperty("jalaliDate", s.getJalaliDate());

    // OAuth2 handler
    engine.rootContext()->setContextProperty("oauth2", s.getOAuth2());

    // User details UI class
    engine.rootContext()->setContextProperty("userDetails", s.getUiUserDetails());

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
