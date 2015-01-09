#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>


// Jalali date
#include "cjalalidate.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    // Requeired C++ Classes
    CJalaliDate jdate;


    QQmlApplicationEngine engine;

    // Add C++ Classes to QML engine
    engine.rootContext()->setContextProperty("JDate", QVariant::fromValue(&jdate));

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
