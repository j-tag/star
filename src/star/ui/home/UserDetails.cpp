#include "includes/star/Star.hpp"

star::ui::home::UserDetails::UserDetails() {}

star::ui::home::UserDetails::~UserDetails() {}

void star::ui::home::UserDetails::updateName(const QString &strName)
{
    this->_strName = strName;
    emit this->nameChanged(strName);
}

QString star::ui::home::UserDetails::getName()
{
    return this->_strName;
}
