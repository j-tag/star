#include "includes/star/Star.hpp"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


star::date::events::TodayEvents::TodayEvents() {}

star::date::events::TodayEvents::~TodayEvents() {}

void star::date::events::TodayEvents::reload()
{
    QString patternUrl("apps/fa/star-v4/calendar-event/$YEAR/$MONTH/$DAY.json");

    auto strUrl = patternUrl.replace("$YEAR", s.getJalaliDate()->getCurrentJalaliYear())
            .replace("$MONTH", s.getJalaliDate()->getCurrentJalaliMonth())
            .replace("$DAY", s.getJalaliDate()->getCurrentJalaliDayInMonth());

    s.getWebAccessManager()->withAuthenticationHeader()->get(s.getUrlManager()->getPureUrl(strUrl), [=](QNetworkReply *reply, int ) {
        // Read data
        auto jsoc = QJsonDocument::fromJson(reply->readAll());
        auto json = jsoc.object();

        // Holiday
        this->_bHoliday = json["holiday"].toBool();

        // Events
        this->_varLstEvents = json["events"].toArray().toVariantList();

        // Islamic date
        this->_strIslamicDate = json["islamicDate"].toString();

        // Persian date
        this->_strPersianDate = json["persianDate"].toString();

        // Gregorian date
        this->_strGregorianDate = json["gregorianDate"].toString();

        // Populate changes
        emit this->eventsChanged(this->_varLstEvents, this->_bHoliday);
    });
}

QVariantList star::date::events::TodayEvents::getEvents() const
{
    return this->_varLstEvents;
}

bool star::date::events::TodayEvents::isHoliday()
{
    return this->_bHoliday;
}

QString star::date::events::TodayEvents::getIslamicDate() const
{
    return this->_strIslamicDate;
}

QString star::date::events::TodayEvents::getPersianDate() const
{
    return this->_strPersianDate;
}

QString star::date::events::TodayEvents::getGregorianDate() const
{
    return this->_strGregorianDate;
}

