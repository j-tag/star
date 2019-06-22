#include "includes/star/Star.hpp"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


star::date::events::TodayEvents::TodayEvents() {}

star::date::events::TodayEvents::~TodayEvents() {}

void star::date::events::TodayEvents::reload()
{
    QString patternUrl("apps/fa/star-v3/calendar-event/$YEAR/$MONTH/$DAY.json");

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

