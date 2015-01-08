#ifndef CJALALIDATE_H
#define CJALALIDATE_H

#include <QObject>
#include <QJSValue>
#include <QQmlEngine>
#include <QDateTime>


class CJalaliDate : public QObject
{
    Q_OBJECT

public:
    explicit CJalaliDate(QObject *parent = 0);
    ~CJalaliDate();

    static QJSValue getCurrentJalaliDate(QQmlEngine *engine, QJSEngine *scriptEngine);

protected:
    static QString gregorianToJalali(const int year, const int month, const int day);
    static QString jalaliToGregorian(const int year, const int month, const int day);

signals:

public slots:
};

#endif // CJALALIDATE_H
