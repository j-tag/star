#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

// Jalali date
#include "cjalalidate.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Register C++ Methodes
    qmlRegisterSingletonType("PureSoft.JalaliDate.currentJalaliDate", 1, 0, "JalaliDate", CJalaliDate::getCurrentJalaliDate);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
