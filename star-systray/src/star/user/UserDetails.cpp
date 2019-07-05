#include "includes/star/Star.hpp"

star::user::UserDetails::UserDetails() {}

star::user::UserDetails::~UserDetails() {}

void star::user::UserDetails::updateName(const QString &strName)
{
    this->_strName = strName;
    emit this->nameChanged(strName);
}

void star::user::UserDetails::updateBirthday(const QDateTime &dateTimeBirthday)
{
    this->_dateTimeBirthday = dateTimeBirthday;
    emit this->birthdayChanged(dateTimeBirthday);
}

void star::user::UserDetails::updateShowBirthVariants(bool bShowBirthVariants)
{
    this->_bShowBirthVariants = bShowBirthVariants;
    emit this->showBirthVariantsChanged(this->_bShowBirthVariants);
}

void star::user::UserDetails::updateCelebrateBirthday(bool bCelebrateBirthday)
{
    this->_bCelebrateBirthday = bCelebrateBirthday;
    emit this->celebrateBirthdayChanged(this->_bCelebrateBirthday);
}

void star::user::UserDetails::updateAutoStart(bool bAutoStart)
{
    this->_bAutoStart = bAutoStart;
    emit this->autoStartChanged(this->_bAutoStart);
}

QDateTime star::user::UserDetails::getBirthday() const
{
    return this->_dateTimeBirthday;
}

bool star::user::UserDetails::getShowBirthVariants()
{
    return this->_bShowBirthVariants;
}

bool star::user::UserDetails::getCelebrateBirthday()
{
    return this->_bCelebrateBirthday;
}

bool star::user::UserDetails::getAutoStart()
{
    return this->_bAutoStart;
}

QString star::user::UserDetails::getName() const
{
    return this->_strName;
}

void star::user::UserDetails::updateAge() {
    emit this->invalidateAge();
}
