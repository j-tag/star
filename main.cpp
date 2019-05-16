#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>


// Jalali date
#include "includes/date/CJalaliDate.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    // Requeired C++ Classes
    CJalaliDate jdate;


    QQmlApplicationEngine engine;

    // Add C++ Classes to QML engine
    engine.rootContext()->setContextProperty("JDate", QVariant::fromValue(&jdate));

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
