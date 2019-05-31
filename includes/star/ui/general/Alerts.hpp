#ifndef ALERTS_HPP
#define ALERTS_HPP

#include <QObject>

namespace star {

namespace ui {

namespace general {

class Alerts : public QObject
{
    Q_OBJECT
public:
    Alerts();
    virtual ~Alerts();

signals:
    void showError(QString strMessage);

public slots:
    void showErrorMessage(const QString &strMessage);
};

}

}

}
#endif // ALERTS_HPP
