#include "includes/star/Star.hpp"
#include "includes/star/date/HijriDate.hpp"

star::date::HijriDateCalculator::HijriDateCalculator() {}

star::date::HijriDateCalculator::~HijriDateCalculator() {}

QString star::date::HijriDateCalculator::getCurrentHijriDate() const
{

    int days{static_cast<int>(QDate(1, 1, 1).daysTo(QDate::currentDate()))};

    auto hijriDate = new star::date::HijriDate(days);

    return QString("%1/%2/%3").arg(hijriDate->getYear())
            .arg(hijriDate->getMonth(), 2, 10, QChar('0'))
            .arg(hijriDate->getDay(), 2, 10, QChar('0'));
}
