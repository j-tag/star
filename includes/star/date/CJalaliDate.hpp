#ifndef CJALALIDATE_H
#define CJALALIDATE_H

#include <QObject>
#include <QDateTime>

namespace star {

namespace date {

class CJalaliDate : public QObject
{
    Q_OBJECT

public:

    explicit CJalaliDate(QObject *parent = nullptr);
    ~CJalaliDate();

signals:

public slots:
    QString getCurrentGregorianDate() const;
    QString getCurrentJalaliDate() const;
    QString getCurrentJalaliYear() const;
    QString getCurrentJalaliMonth() const;
    QString getCurrentJalaliDayInMonth() const;
    qint64 getCurrentJalaliDayInYear() const;
    QString getCurrentJalaliDayName() const;
    int getCurrentMillisecondOfDay() const;
    QString jalaliToGregorian(const int year, const int month, const int day) const;
    qint64 jalaliToUnixTimestamp(const int year, const int month, const int day) const;
    qint64 secondsDiffTillNow(const QDateTime &dateTime);
    qint64 minutesDiffTillNow(const QDateTime &dateTime);
    qint64 hoursDiffTillNow(const QDateTime &dateTime);
    qint64 daysDiffTillNow(const QDateTime &dateTime);
    qint64 weeksDiffTillNow(const QDateTime &dateTime);
    qint64 monthsDiffTillNow(const QDateTime &dateTime);
    qint64 seasonsDiffTillNow(const QDateTime &dateTime);
    qint64 yearsDiffTillNow(const QDateTime &dateTime);

protected:
    QString gregorianToJalali(const int year, const int month, const int day) const;


};


}

}


#endif // CJALALIDATE_H
