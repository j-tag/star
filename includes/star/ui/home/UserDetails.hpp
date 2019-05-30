#ifndef USERDETAILS_HPP
#define USERDETAILS_HPP

#include <QObject>

namespace star {

namespace ui {

namespace home {

class UserDetails : public QObject
{
public:
    Q_PROPERTY(QString name READ getName NOTIFY nameChanged)


    Q_OBJECT
public:
    UserDetails();
    virtual ~UserDetails();

    void updateName(const QString &strName);

signals:
    void nameChanged(QString name);

public slots:
    QString getName();

private:
    QString _strName;
};

}

}

}

#endif // USERDETAILS_HPP
