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
    Q_PROPERTY(bool showBirthVariants READ getShowBirthVariants NOTIFY showBirthVariantsChanged)
    Q_PROPERTY(bool celebrateBirthday READ getCelebrateBirthday NOTIFY celebrateBirthdayChanged)
    Q_PROPERTY(bool autoStart READ getAutoStart NOTIFY autoStartChanged)


    Q_OBJECT
public:
    UserDetails();
    virtual ~UserDetails();

    void updateName(const QString &strName);
    void updateBirthday(const QDateTime &dateTimeBirthday);
    void updateShowBirthVariants(bool bShowBirthVariants);
    void updateCelebrateBirthday(bool bCelebrateBirthday);
    void updateAutoStart(bool bAutoStart);

signals:
    void nameChanged(QString name);
    void birthdayChanged(QDateTime birthday);
    void invalidateAge();
    void showBirthVariantsChanged(bool bShowBirthVariants);
    void celebrateBirthdayChanged(bool bCelebrateBirthday);
    void autoStartChanged(bool bAutoStart);

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
    bool getShowBirthVariants();
    bool getCelebrateBirthday();
    bool getAutoStart();

private:
    QString _strName;
    QDateTime _dateTimeBirthday;
    bool _bShowBirthVariants;
    bool _bCelebrateBirthday;
    bool _bAutoStart;
};

}

}

}

#endif // USERDETAILS_HPP
