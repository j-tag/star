#include "includes/star/Star.hpp"


star::date::CJalaliDate::CJalaliDate(QObject *parent) : QObject(parent)
{

}

star::date::CJalaliDate::~CJalaliDate()
{

}

QString star::date::CJalaliDate::getCurrentGregorianDate() const
{
    return QDate::currentDate().toString("yyyy/MM/dd");
}

/* -------------- Date Functions -------------- */

// Get Gregorian Date and Convert it to Jalali Date
QString star::date::CJalaliDate::gregorianToJalali(int year, int month, int day) const
{
    QString result;
    int tmpYear = year - 1;
    int tmpMonth = month - 1;
    int tmpDay = 0;

    if (year % 4 == 0)
    {
        if(tmpMonth == 0) tmpDay = (int(tmpYear * 365.25)) + day;
        if(tmpMonth == 1) tmpDay = (int(tmpYear * 365.25)) + 31 + day;
        if(tmpMonth == 2) tmpDay = (int(tmpYear * 365.25)) + 31 + 29 + day;
        if(tmpMonth == 3) tmpDay = (int(tmpYear * 365.25)) + 31 + 29 + 31 + day;
        if(tmpMonth == 4) tmpDay = (int(tmpYear * 365.25)) + 31 + 29 + 31 + 30 + day;
        if(tmpMonth == 5) tmpDay = (int(tmpYear * 365.25)) + 31 + 29 + 31 + 30 + 31 + day;
        if(tmpMonth == 6) tmpDay = (int(tmpYear * 365.25)) + 31 + 29 + 31 + 30 + 31 + 30 + day;
        if(tmpMonth == 7) tmpDay = (int(tmpYear * 365.25)) + 31 + 29 + 31 + 30 + 31 + 30 + 31 + day;
        if(tmpMonth == 8) tmpDay = (int(tmpYear * 365.25)) + 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + day;
        if(tmpMonth == 9) tmpDay = (int(tmpYear * 365.25)) + 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + day;
        if(tmpMonth == 10) tmpDay = (int(tmpYear * 365.25)) + 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + day;
        if(tmpMonth == 11) tmpDay = (int(tmpYear * 365.25)) + 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + day;
    }
    else
    {
        if(tmpMonth == 0) tmpDay = (int(tmpYear * 365.25)) + day;
        if(tmpMonth == 1) tmpDay = (int(tmpYear * 365.25)) + 31 + day;
        if(tmpMonth == 2) tmpDay = (int(tmpYear * 365.25)) + 31 + 28 + day;
        if(tmpMonth == 3) tmpDay = (int(tmpYear * 365.25)) + 31 + 28 + 31 + day;
        if(tmpMonth == 4) tmpDay = (int(tmpYear * 365.25)) + 31 + 28 + 31 + 30 + day;
        if(tmpMonth == 5) tmpDay = (int(tmpYear * 365.25)) + 31 + 28 + 31 + 30 + 31 + day;
        if(tmpMonth == 6) tmpDay = (int(tmpYear * 365.25)) + 31 + 28 + 31 + 30 + 31 + 30 + day;
        if(tmpMonth == 7) tmpDay = (int(tmpYear * 365.25)) + 31 + 28 + 31 + 30 + 31 + 30 + 31 + day;
        if(tmpMonth == 8) tmpDay = (int(tmpYear * 365.25)) + 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + day;
        if(tmpMonth == 9) tmpDay = (int(tmpYear * 365.25)) + 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + day;
        if(tmpMonth == 10) tmpDay = (int(tmpYear * 365.25)) + 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + day;
        if(tmpMonth == 11) tmpDay = (int(tmpYear * 365.25)) + 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + day;
    }

    tmpDay = tmpDay - 226899;

    int resultYear = int(tmpDay / 365.25) + 1 ;
    int auxYear = int(tmpDay / 365.25);

    tmpDay = tmpDay - int( int(auxYear * 365.25) + .25 );

    int resultMonth, resultDay;

    if (resultYear % 4 == 3) tmpDay = tmpDay + 1;

    if(tmpDay > 336) {
        resultMonth = 12; resultDay = tmpDay - 336;
    }
    else if(tmpDay > 306) {
        resultMonth = 11; resultDay = tmpDay - 306;
    }
    else if(tmpDay > 276) {
        resultMonth = 10; resultDay = tmpDay - 276;
    }
    else if(tmpDay > 246) {
        resultMonth = 9; resultDay = tmpDay - 246;
    }
    else if(tmpDay > 216) {
        resultMonth = 8; resultDay = tmpDay - 216;
    }
    else if(tmpDay > 186) {
        resultMonth = 7; resultDay = tmpDay - 186;
    }
    else if(tmpDay > 155) {
        resultMonth = 6; resultDay = tmpDay - 155;
    }
    else if(tmpDay > 124) {
        resultMonth = 5; resultDay = tmpDay - 124;
    }
    else if(tmpDay > 93) {
        resultMonth = 4; resultDay = tmpDay - 93;
    }
    else if(tmpDay > 62) {
        resultMonth = 3; resultDay = tmpDay - 62;
    }
    else if(tmpDay > 31) {
        resultMonth = 2; resultDay = tmpDay - 31;
    }
    else if(tmpDay > 0) {
        resultMonth = 1; resultDay = tmpDay;
    }
    else {
        if(resultYear % 4 != 0) {
            resultYear = resultYear - 1; resultMonth = 12; resultDay = 29;
        }
        else {
            resultYear = resultYear - 1; resultMonth = 12; resultDay = 30;
        }
    }

    if (resultMonth <= 9 && resultDay <= 9)
        result = QString("%1/0%2/0%3").arg(resultYear).arg(resultMonth).arg(resultDay);
    else if(resultMonth <= 9)
        result = QString("%1/0%2/%3").arg(resultYear).arg(resultMonth).arg(resultDay);
    else if(resultDay <= 9)
        result = QString("%1/%2/0%3").arg(resultYear).arg(resultMonth).arg(resultDay);
    else
        result = QString("%1/%2/%3").arg(resultYear).arg(resultMonth).arg(resultDay);

    return result;
}

QString star::date::CJalaliDate::getJalaliMonthName(int month) const
{
    switch (month) {
    case 1:
        return QStringLiteral("فروردین");
    case 2:
        return QStringLiteral("اردیبهشت");
    case 3:
        return QStringLiteral("خرداد");
    case 4:
        return QStringLiteral("تیر");
    case 5:
        return QStringLiteral("مرداد");
    case 6:
        return QStringLiteral("شهریور");
    case 7:
        return QStringLiteral("مهر");
    case 8:
        return QStringLiteral("آبان");
    case 9:
        return QStringLiteral("آذر");
    case 10:
        return QStringLiteral("دی");
    case 11:
        return QStringLiteral("بهمن");
    case 12:
        return QStringLiteral("اسفند");
    default:
        return QStringLiteral("");
    }
}

// Get Jalali Date and Convert it to Gregorian Date
QString star::date::CJalaliDate::jalaliToGregorian(int year, int month, int day) const
{
    QString result;
    int tmpYear = year -1;
    int tmpMonth = month -1;
    int tmpDay = day;

    if(tmpMonth <= 6 ) tmpDay = int( int(tmpYear * 365.25) + (tmpMonth * 31) + tmpDay + .25 );
    else tmpDay = int( int(tmpYear * 365.25) + (tmpMonth - 6) * 30 + 186 + tmpDay + .25 );

    tmpDay = tmpDay + 226899;
    int resultYear = int(tmpDay / 365.25) + 1;
    int auxYear = int(tmpDay / 365.25);
    auxYear = int(auxYear * 365.25);
    tmpDay = tmpDay - auxYear;
    int resultMonth = 0, resultDay = 0;

    if(resultYear % 4 == 0)
    {
        if(tmpDay == 0) {
            resultYear = resultYear - 1;
            resultMonth = 12;
            resultDay = 31;
        }

        if(tmpDay <= 31) {
            resultMonth = 1; resultDay = tmpDay;
        }
        else if(tmpDay <= 60) {
            resultMonth = 2; resultDay = tmpDay - 31;
        }
        else if(tmpDay <= 91) {
            resultMonth = 3; resultDay = tmpDay - 60;
        }
        else if(tmpDay <= 121) {
            resultMonth = 4; resultDay = tmpDay - 91;
        }
        else if(tmpDay <= 152) {
            resultMonth = 5; resultDay = tmpDay - 121;
        }
        else if(tmpDay <= 182) {
            resultMonth = 6; resultDay = tmpDay - 152;
        }
        else if(tmpDay <= 213) {
            resultMonth = 7; resultDay = tmpDay - 182;
        }
        else if(tmpDay <= 244) {
            resultMonth = 8; resultDay = tmpDay - 213;
        }
        else if(tmpDay <= 274) {
            resultMonth = 9; resultDay = tmpDay - 244;
        }
        else if(tmpDay <= 305) {
            resultMonth = 10; resultDay = tmpDay - 274;
        }
        else if(tmpDay <= 335) {
            resultMonth = 11; resultDay = tmpDay - 305;
        }
        else if(tmpDay <= 366) {
            resultMonth = 12; resultDay = tmpDay - 335;
        }
    }
    else
    {
        if(tmpDay==0) {
            resultYear = resultYear - 1; resultMonth = 12; resultDay = 31;
        }
        else if(tmpDay <= 31) {
            resultMonth = 1; resultDay = tmpDay;
        }
        else if(tmpDay <= 59) {
            resultMonth = 2; resultDay = tmpDay - 31;
        }
        else if(tmpDay <= 90) {
            resultMonth = 3; resultDay = tmpDay - 59;
        }
        else if(tmpDay <= 120) {
            resultMonth = 4; resultDay = tmpDay - 90;
        }
        else if(tmpDay <= 151) {
            resultMonth = 5; resultDay = tmpDay - 120;
        }
        else if(tmpDay <= 181) {
            resultMonth = 6; resultDay = tmpDay - 151;
        }
        else if(tmpDay <= 212) {
            resultMonth = 7; resultDay = tmpDay - 181;
        }
        else if(tmpDay <= 243) {
            resultMonth = 8; resultDay = tmpDay - 212;
        }
        else if(tmpDay <= 273) {
            resultMonth = 9; resultDay = tmpDay - 243;
        }
        else if(tmpDay <= 304) {
            resultMonth = 10; resultDay = tmpDay - 273;
        }
        else if(tmpDay <= 334) {
            resultMonth = 11; resultDay = tmpDay - 304;
        }
        else if(tmpDay < 366) {
            resultMonth = 12; resultDay = tmpDay - 334;
        }
        else {
            resultYear = resultYear + 1; resultMonth = 1; resultDay = 1;
        }
    }

    if (resultMonth <= 9 && resultDay <= 9)
        result = QString("%1/0%2/0%3").arg(resultYear).arg(resultMonth).arg(resultDay);
    else if(resultMonth <= 9)
        result = QString("%1/0%2/%3").arg(resultYear).arg(resultMonth).arg(resultDay);
    else if(resultDay <= 9)
        result = QString("%1/%2/0%3").arg(resultYear).arg(resultMonth).arg(resultDay);
    else
        result = QString("%1/%2/%3").arg(resultYear).arg(resultMonth).arg(resultDay);

    return result;
}

/* -------------- /Date Functions -------------- */

qint64 star::date::CJalaliDate::jalaliToUnixTimestamp(const int year, const int month, const int day) const
{
    QDateTime date = QDateTime::fromString(this->jalaliToGregorian(year, month, day), "yyyy/MM/dd");

    return date.toSecsSinceEpoch();
}

qint64 star::date::CJalaliDate::jalaliToUnixTimestamp(const QString &strDate) const
{
    return this->jalaliToUnixTimestamp(strDate.left(4).toInt(), strDate.mid(5,2).toInt(), strDate.right(2).toInt());
}

QString star::date::CJalaliDate::unixTimestampToJalali(int timestamp) const
{
    auto date = QDateTime::fromSecsSinceEpoch(timestamp).date();
    return this->gregorianToJalali(date.year(), date.month(), date.day());
}

qint64 star::date::CJalaliDate::secondsDiffTillNow(const QDateTime &dateTime)
{
    return dateTime.secsTo(QDateTime::currentDateTime());
}

qint64 star::date::CJalaliDate::minutesDiffTillNow(const QDateTime &dateTime)
{
    return this->secondsDiffTillNow(dateTime) / 60;
}

qint64 star::date::CJalaliDate::hoursDiffTillNow(const QDateTime &dateTime)
{
    return this->minutesDiffTillNow(dateTime) / 60;
}

qint64 star::date::CJalaliDate::daysDiffTillNow(const QDateTime &dateTime)
{
    return dateTime.daysTo(QDateTime::currentDateTime());
}

qint64 star::date::CJalaliDate::weeksDiffTillNow(const QDateTime &dateTime)
{
    return this->daysDiffTillNow(dateTime) / 7;
}

qint64 star::date::CJalaliDate::monthsDiffTillNow(const QDateTime &dateTime)
{
    return this->daysDiffTillNow(dateTime) / 30;
}

qint64 star::date::CJalaliDate::seasonsDiffTillNow(const QDateTime &dateTime)
{
    return this->monthsDiffTillNow(dateTime) / 3;
}

qint64 star::date::CJalaliDate::yearsDiffTillNow(const QDateTime &dateTime)
{
    return this->monthsDiffTillNow(dateTime) / 12;
}

QString star::date::CJalaliDate::getJalaliYear(const QDateTime &dateTime) const
{
    QDate date(dateTime.date());

    const QString jalaliDate = this->gregorianToJalali(date.year(), date.month(), date.day());

    return jalaliDate.left(4);
}

QString star::date::CJalaliDate::getJalaliMonth(const QDateTime &dateTime) const
{
    QDate date(dateTime.date());

    const QString jalaliDate = this->gregorianToJalali(date.year(), date.month(), date.day());

    return jalaliDate.mid(5,2);
}

QString star::date::CJalaliDate::getJalaliDayInMonth(const QDateTime &dateTime) const
{
    QDate date(dateTime.date());

    const QString jalaliDate = this->gregorianToJalali(date.year(), date.month(), date.day());

    return jalaliDate.right(2);
}

QString star::date::CJalaliDate::getMiniDate(int timestamp) const
{
    auto jalaliDate = this->unixTimestampToJalali(timestamp);
    return jalaliDate.right(2) + " ،" + this->getJalaliMonthName(jalaliDate.mid(5,2).toInt());
}

QString star::date::CJalaliDate::getCurrentJalaliDate() const
{
    QDate date(QDate::currentDate());

    const QString currentJalaliDate = this->gregorianToJalali(date.year(), date.month(), date.day());

    return currentJalaliDate;
}

QString star::date::CJalaliDate::getCurrentJalaliYear() const
{
    return this->getCurrentJalaliDate().left(4);
}

QString star::date::CJalaliDate::getCurrentJalaliMonth() const
{
    return this->getCurrentJalaliDate().mid(5,2);
}

QString star::date::CJalaliDate::getCurrentJalaliDayInMonth() const
{
    return this->getCurrentJalaliDate().right(2);
}

qint64 star::date::CJalaliDate::getCurrentJalaliDayInYear() const
{
    QDate startDate = QDate::fromString(this->jalaliToGregorian(this->getCurrentJalaliYear().toInt(), 1, 1), "yyyy/MM/dd");

    QDate endDate = QDate::fromString(this->jalaliToGregorian(this->getCurrentJalaliYear().toInt(), this->getCurrentJalaliMonth().toInt()
                        , this->getCurrentJalaliDayInMonth().toInt()), "yyyy/MM/dd");

    qInfo() << "Days from start of year till now:" << startDate.daysTo(endDate);

    return startDate.daysTo(endDate);
}

QString star::date::CJalaliDate::getCurrentJalaliDayName() const
{
    QString result;

    switch (QDate::currentDate().dayOfWeek())
    {
    case 1:
        result = "دوشنبه";
        break;
    case 2:
        result = "سه شنبه";
        break;
    case 3:
        result = "چهارشنبه";
        break;
    case 4:
        result = "پنج شنبه";
        break;
    case 5:
        result = "جمعه";
        break;
    case 6:
        result = "شنبه";
        break;
    case 7:
        result = "یکشنبه";
        break;
    default:
        break;
    }

    return result;
}

int star::date::CJalaliDate::getCurrentMillisecondOfDay() const
{
    return QTime::currentTime().msecsSinceStartOfDay();
}
