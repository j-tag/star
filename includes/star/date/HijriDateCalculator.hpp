#ifndef HIJRIDATECALCULATOR_HPP
#define HIJRIDATECALCULATOR_HPP

#include <QObject>

namespace star {

namespace date {

class HijriDateCalculator : public QObject
{
    Q_OBJECT
public:
    HijriDateCalculator();
    virtual ~HijriDateCalculator();

public slots:
    QString getCurrentHijriDate() const;
};

}

}

#endif // HIJRIDATECALCULATOR_HPP
