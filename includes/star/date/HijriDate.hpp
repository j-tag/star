#ifndef HIJRIDATE_HPP
#define HIJRIDATE_HPP

namespace star {

namespace date {

class HijriDate
{

public:

    HijriDate();
    HijriDate(int y, int m, int d);

    // Computes the Islamic date from the absolute date.
    explicit HijriDate(int jdn);

    ~HijriDate();

    // Computes the absolute date from the Islamic date.
    operator int();

    // True if year is an Islamic leap year
    bool isLeapYear() const {return isLeapYear(year);}

    // Last day in month during year on the Islamic calendar.
    int LastDayOfMonth() const { return LastDayOfMonth(month, year); }

    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    // static functions
    static bool isLeapYear(int y);
    static int LastDayOfMonth(int m, int y);

private:
    int year;   // 1...
    int month;  // 1..13 (12 in a common year)
    int day;    // 1..lastDayOfMonth(month,year)
};

}

}


#endif // HIJRIDATE_HPP
