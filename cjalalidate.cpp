#include "cjalalidate.h"

#include <QDebug>



CJalaliDate::CJalaliDate(QObject *parent) : QObject(parent)
{

}

CJalaliDate::~CJalaliDate()
{

}

/* -------------- Date Functions -------------- */

// Get Gregorian Date and Convert it to Jalali Date
QString CJalaliDate::gregorianToJalali(int year, int month, int day) const
{
    QString result;
    int s=year-1;
    int m=month-1;
    int r;

    if (year%4==0)
    {
        if(m==0) r=(s*365.25)+day;
        if(m==1) r=(s*365.25)+31+day;
        if(m==2) r=(s*365.25)+31+29+day;
        if(m==3) r=(s*365.25)+31+29+31+day;
        if(m==4) r=(s*365.25)+31+29+31+30+day;
        if(m==5) r=(s*365.25)+31+29+31+30+31+day;
        if(m==6) r=(s*365.25)+31+29+31+30+31+30+day;
        if(m==7) r=(s*365.25)+31+29+31+30+31+30+31+day;
        if(m==8) r=(s*365.25)+31+29+31+30+31+30+31+31+day;
        if(m==9) r=(s*365.25)+31+29+31+30+31+30+31+31+30+day;
        if(m==10) r=(s*365.25)+31+29+31+30+31+30+31+31+30+31+day;
        if(m==11) r=(s*365.25)+31+29+31+30+31+30+31+31+30+31+30+day;
    }
    else
    {
        if(m==0) r=(s*365.25)+day;
        if(m==1) r=(s*365.25)+31+day;
        if(m==2) r=(s*365.25)+31+28+day;
        if(m==3) r=(s*365.25)+31+28+31+day;
        if(m==4) r=(s*365.25)+31+28+31+30+day;
        if(m==5) r=(s*365.25)+31+28+31+30+31+day;
        if(m==6) r=(s*365.25)+31+28+31+30+31+30+day;
        if(m==7) r=(s*365.25)+31+28+31+30+31+30+31+day;
        if(m==8) r=(s*365.25)+31+28+31+30+31+30+31+31+day;
        if(m==9) r=(s*365.25)+31+28+31+30+31+30+31+31+30+day;
        if(m==10) r=(s*365.25)+31+28+31+30+31+30+31+31+30+31+day;
        if(m==11) r=(s*365.25)+31+28+31+30+31+30+31+31+30+31+30+day;
    }
    r=r-226899;
    int sa=(r/365.25)+1 ;
    int ss=r/365.25;
    r=r-(ss*365.25)+.25;
    int ma,ro;
    if (sa%4==3) r=r+1;
    if(r>336) ma=12,ro=r-336;
    else if(r>306) ma=11 ,ro=r-306;
    else  if(r>276) ma=10 ,ro=r-276;
    else  if(r>246) ma=9 ,ro=r-246;
    else  if(r>216) ma=8 ,ro=r-216;
    else  if(r>186) ma=7 ,ro=r-186;
    else  if(r>155) ma=6 ,ro=r-155;
    else  if(r>124) ma=5 ,ro=r-124;
    else  if(r>93) ma=4 ,ro=r-93;
    else  if(r>62) ma=3 ,ro=r-62;
    else  if(r>31) ma=2 ,ro=r-31;
    else  if(r>0) ma=1,ro=r;
    else if(r==0)
    {
        if(sa%4!=0)sa=sa-1,ma=12,ro=29;
        else sa=sa-1,ma=12,ro=30;
    }

    if (ma<=9 && ro<=9)
        result = QString("%1/0%2/0%3").arg(sa).arg(ma).arg(ro);
    else if(ma<=9)
        result = QString("%1/0%2/%3").arg(sa).arg(ma).arg(ro);
    else if(ro<=9)
        result = QString("%1/%2/0%3").arg(sa).arg(ma).arg(ro);
    else
        result = QString("%1/%2/%3").arg(sa).arg(ma).arg(ro);

    return result;
}

// Get Jalali Date and Convert it to Gregorian Date
QString CJalaliDate::jalaliToGregorian(int year, int month, int day) const
{
    QString result;
    int s=year -1;
    int m=month -1;
    int r=day;
    if(m<=6 ) r=(s*365.25)+(m*31)+r+.25;
    else r=(s*365.25)+(m-6)*30+186 + r+.25;
    r=r+226899;
    int sa=(r/365.25)+1;
    int ss=r/365.25;
    ss=ss*365.25;
    r=r-ss;
    int ma,ro;
    if(sa%4==0)
    {
        if(r==0) sa=sa-1,ma=12,ro=31;
        if(r<=31) ma=1, ro=r;
        else if(r<=60) ma=2, ro=r-31;
        else if(r<=91) ma=3, ro=r-60;
        else if(r<=121) ma=4, ro=r-91;
        else if(r<=152) ma=5, ro=r-121;
        else if(r<=182) ma=6, ro=r-152;
        else if(r<=213) ma=7, ro=r-182;
        else if(r<=244) ma=8, ro=r-213;
        else if(r<=274) ma=9, ro=r-244;
        else if(r<=305) ma=10, ro=r-274;
        else if(r<=335) ma=11, ro=r-305;
        else if(r<=366) ma=12, ro=r-335;
    }
    else
    {
        if(r==0) sa=sa-1,ma=12,ro=31;
        else if(r<=31) ma=1, ro=r;
        else if(r<=59) ma=2, ro=r-31;
        else if(r<=90) ma=3, ro=r-59;
        else if(r<=120) ma=4, ro=r-90;
        else if(r<=151) ma=5, ro=r-120;
        else if(r<=181) ma=6, ro=r-151;
        else if(r<=212) ma=7, ro=r-181;
        else if(r<=243) ma=8, ro=r-212;
        else if(r<=273) ma=9, ro=r-243;
        else if(r<=304) ma=10, ro=r-273;
        else if(r<=334) ma=11, ro=r-304;
        else if(r<366) ma=12, ro=r-334;
        else if (r=366) sa=sa+1,ma=1 , ro=1;
    }

    if (ma<=9 && ro<=9)
        result = QString("%1/0%2/0%3").arg(sa).arg(ma).arg(ro);
    else if(ma<=9)
        result = QString("%1/0%2/%3").arg(sa).arg(ma).arg(ro);
    else if(ro<=9)
        result = QString("%1/%2/0%3").arg(sa).arg(ma).arg(ro);
    else
        result = QString("%1/%2/%3").arg(sa).arg(ma).arg(ro);

    return result;
}

/* -------------- /Date Functions -------------- */

QString CJalaliDate::getCurrentJalaliDate() const
{
    QDate date(QDate::currentDate());

    const QString currentJalaliDate = gregorianToJalali(date.year(), date.month(), date.day());

    qDebug() << "Current Gregorian date:" << date.year() << "/" << date.month() << "/" << date.day();

    qDebug() << "Current Jalali date:" << currentJalaliDate;

    return currentJalaliDate;
}

QString CJalaliDate::getCurrentJalaliYear() const
{
    return this->getCurrentJalaliDate().left(4);
}

QString CJalaliDate::getCurrentJalaliMonth() const
{
    return this->getCurrentJalaliDate().mid(5,2);
}

QString CJalaliDate::getCurrentJalaliDayInMonth() const
{
    return this->getCurrentJalaliDate().right(2);
}

qint64 CJalaliDate::getCurrentJalaliDayInYear() const
{
    QDate startDate(QDate(JalaliDateOptions::CurrentYear, 1, 1));

    QDate endDate(QDate(this->getCurrentJalaliYear().toInt(), this->getCurrentJalaliMonth().toInt()
                        , this->getCurrentJalaliDayInMonth().toInt()));

    qDebug() << "Days from start of year till now:" << startDate.daysTo(endDate);

    return startDate.daysTo(endDate);
}
