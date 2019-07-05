#ifndef USERDETAILS_HPP
#define USERDETAILS_HPP

#include <QObject>
#include <QDateTime>

namespace star {

namespace user {

class UserDetails : public QObject
{
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

#endif // USERDETAILS_HPP
