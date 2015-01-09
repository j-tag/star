#ifndef CJALALIDATE_H
#define CJALALIDATE_H

#include <QObject>
#include <QDateTime>


class CJalaliDate : public QObject
{
    Q_OBJECT

public:
    enum JalaliDateOptions
    {
        CurrentYear = 1393
    };

    explicit CJalaliDate(QObject *parent = 0);
    ~CJalaliDate();

    Q_INVOKABLE QString getCurrentJalaliDate() const;
    Q_INVOKABLE QString getCurrentJalaliYear() const;
    Q_INVOKABLE QString getCurrentJalaliMonth() const;
    Q_INVOKABLE QString getCurrentJalaliDayInMonth() const;
    Q_INVOKABLE qint64 getCurrentJalaliDayInYear() const;


protected:
    QString gregorianToJalali(const int year, const int month, const int day) const;
    QString jalaliToGregorian(const int year, const int month, const int day) const;

signals:

public slots:
};

#endif // CJALALIDATE_H
