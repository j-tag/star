#include "includes/star/Star.hpp"

star::ui::home::UserDetails::UserDetails() {}

star::ui::home::UserDetails::~UserDetails() {}

void star::ui::home::UserDetails::updateName(const QString &strName)
{
    this->_strName = strName;
    emit this->nameChanged(strName);
}

void star::ui::home::UserDetails::updateBirthday(const QDateTime &dateTimeBirthday)
{
    this->_dateTimeBirthday = dateTimeBirthday;
    emit this->birthdayChanged(dateTimeBirthday);
}

void star::ui::home::UserDetails::updateShowBirthVariants(bool bShowBirthVariants)
{
    this->_bShowBirthVariants = bShowBirthVariants;
    emit this->showBirthVariantsChanged(this->_bShowBirthVariants);
}

void star::ui::home::UserDetails::updateCelebrateBirthday(bool bCelebrateBirthday)
{
    this->_bCelebrateBirthday = bCelebrateBirthday;
    emit this->celebrateBirthdayChanged(this->_bCelebrateBirthday);
}

void star::ui::home::UserDetails::updateAutoStart(bool bAutoStart)
{
    this->_bAutoStart = bAutoStart;
    emit this->autoStartChanged(this->_bAutoStart);
}

QDateTime star::ui::home::UserDetails::getBirthday() const
{
    return this->_dateTimeBirthday;
}

qint64 star::ui::home::UserDetails::getBirthdayInSeconds()
{
    return s.getJalaliDate()->secondsDiffTillNow(this->_dateTimeBirthday);
}

qint64 star::ui::home::UserDetails::getBirthdayInMinutes()
{
    return s.getJalaliDate()->minutesDiffTillNow(this->_dateTimeBirthday);
}

qint64 star::ui::home::UserDetails::getBirthdayInHours()
{
    return s.getJalaliDate()->hoursDiffTillNow(this->_dateTimeBirthday);
}

qint64 star::ui::home::UserDetails::getBirthdayInDays()
{
    return s.getJalaliDate()->daysDiffTillNow(this->_dateTimeBirthday);
}

qint64 star::ui::home::UserDetails::getBirthdayInWeeks()
{
    return s.getJalaliDate()->weeksDiffTillNow(this->_dateTimeBirthday);
}

qint64 star::ui::home::UserDetails::getBirthdayInMonths()
{
    return s.getJalaliDate()->monthsDiffTillNow(this->_dateTimeBirthday);
}

qint64 star::ui::home::UserDetails::getBirthdayInSeasons()
{
    return s.getJalaliDate()->seasonsDiffTillNow(this->_dateTimeBirthday);
}

qint64 star::ui::home::UserDetails::getBirthdayInYears()
{
    return s.getJalaliDate()->yearsDiffTillNow(this->_dateTimeBirthday);
}

bool star::ui::home::UserDetails::getShowBirthVariants()
{
    return this->_bShowBirthVariants;
}

bool star::ui::home::UserDetails::getCelebrateBirthday()
{
    return this->_bCelebrateBirthday;
}

bool star::ui::home::UserDetails::getAutoStart()
{
    return this->_bAutoStart;
}

QString star::ui::home::UserDetails::getName() const
{
    return this->_strName;
}

void star::ui::home::UserDetails::updateAge() {
    emit this->invalidateAge();
}
