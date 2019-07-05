#ifndef BIRTHDAYCHECKER_HPP
#define BIRTHDAYCHECKER_HPP

#include <QObject>

namespace star {

namespace user {

class BirthdayChecker : public QObject
{
    Q_OBJECT
public:
    BirthdayChecker();
    virtual ~BirthdayChecker();

public slots:
    void checkBirthday(bool result, QString strMessage);
};

}

}
#endif // BIRTHDAYCHECKER_HPP
