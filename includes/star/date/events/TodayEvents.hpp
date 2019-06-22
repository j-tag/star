#ifndef TODAYEVENTS_HPP
#define TODAYEVENTS_HPP

#include <QObject>
#include <QVariant>

namespace star {

namespace date {

namespace events {

class TodayEvents : public QObject
{
public:
    Q_PROPERTY(QVariantList events READ getEvents NOTIFY eventsChanged)
    Q_PROPERTY(bool holiday READ isHoliday NOTIFY eventsChanged)

    Q_OBJECT
public:
    TodayEvents();
    virtual ~TodayEvents();

signals:
    void eventsChanged(QVariantList events, bool holiday);

public slots:
    void reload();
    QVariantList getEvents() const;
    bool isHoliday();

private:
    QVariantList _varLstEvents;
    bool _bHoliday;
};

}

}

}

#endif // TODAYEVENTS_HPP
