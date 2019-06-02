#ifndef USERDETAILS_HPP
#define USERDETAILS_HPP

#include <QObject>
#include <QDateTime>

namespace star {

namespace ui {

namespace home {

class UserDetails : public QObject
{
public:
    Q_PROPERTY(QString name READ getName NOTIFY nameChanged)
    Q_PROPERTY(QDateTime birthday READ getBirthday NOTIFY birthdayChanged)
    Q_PROPERTY(qint64 birthdayInSeconds READ getBirthdayInSeconds NOTIFY invalidateAge)
    Q_PROPERTY(qint64 birthdayInMinutes READ getBirthdayInMinutes NOTIFY invalidateAge)
    Q_PROPERTY(qint64 birthdayInHours READ getBirthdayInHours NOTIFY invalidateAge)
    Q_PROPERTY(qint64 birthdayInDays READ getBirthdayInDays NOTIFY invalidateAge)
    Q_PROPERTY(qint64 birthdayInWeeks READ getBirthdayInWeeks NOTIFY invalidateAge)
    Q_PROPERTY(qint64 birthdayInMonths READ getBirthdayInMonths NOTIFY invalidateAge)
    Q_PROPERTY(qint64 birthdayInSeasons READ getBirthdayInSeasons NOTIFY invalidateAge)
    Q_PROPERTY(qint64 birthdayInYears READ getBirthdayInYears NOTIFY invalidateAge)


    Q_OBJECT
public:
    UserDetails();
    virtual ~UserDetails();

    void updateName(const QString &strName);
    void updateBirthday(const QDateTime &dateTimeBirthday);

signals:
    void nameChanged(QString name);
    void birthdayChanged(QDateTime birthday);
    void invalidateAge();

public slots:
    void updateAge();
    QString getName() const;
    QDateTime getBirthday() const;
    qint64 getBirthdayInSeconds();
    qint64 getBirthdayInMinutes();
    qint64 getBirthdayInHours();
    qint64 getBirthdayInDays();
    qint64 getBirthdayInWeeks();
    qint64 getBirthdayInMonths();
    qint64 getBirthdayInSeasons();
    qint64 getBirthdayInYears();

private:
    QString _strName;
    QDateTime _dateTimeBirthday;
};

}

}

}

#endif // USERDETAILS_HPP
