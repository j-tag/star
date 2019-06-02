#include "includes/star/date/HijriDate.hpp"

// Absolute date of start of Islamic calendar
// 19 Jul 622 C.E or 16 July 622 (Julian Calendar) = 1 Muharram 1 A.H.
// JDN = 1948439.5

const int HijriEpoch = 227014;

star::date::HijriDate::HijriDate() {}

star::date::HijriDate::HijriDate(int y, int m, int d) : year(y), month(m), day(d) { }

// Computes the Hijri date from the absolute date.
star::date::HijriDate::HijriDate(int d)
{
    if (d <= HijriEpoch) { // Date is pre-Hijri
        month = 0;
        day = 0;
        year = 0;
    }
    else {
        // Search forward year by year from approximate year
        year = (d - HijriEpoch) / 355;
        while (d >= star::date::HijriDate(year + 1, 1, 1))
            year++;
        // Search forward month by month from Muharram
        month = 1;
        while (d > star::date::HijriDate(year, month, LastDayOfMonth()))
            month++;
        day = d - star::date::HijriDate(year, month, 1) + 1;
    }
}

star::date::HijriDate::~HijriDate() {}

// Computes the absolute date from the Hijri date.
star::date::HijriDate::operator int()
{
    return (day                      // days so far this month
            + 29 * (month - 1)       // days so far...
            + month/2                //            ...this year
            + 354 * (year - 1)       // non-leap days in prior years
            + (3 + (11 * year)) / 30 // leap days in prior years
            + HijriEpoch);         // days before start of calendar
}

// True if year is a Hijri leap year
bool star::date::HijriDate::isLeapYear(int y)
{
    return ((((11 * y) + 14) % 30) < 11) ? true : false;
}

// Last day in month during year on the Hijri calendar.
int star::date::HijriDate::LastDayOfMonth(int m, int y)
{
    return (((m % 2) == 1) || ((m == 12) && isLeapYear(y))) ? 30 : 29;
}
