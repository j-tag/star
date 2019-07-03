#ifndef UPDATEMANAGER_HPP
#define UPDATEMANAGER_HPP

#include <QObject>

namespace star {

namespace web {

namespace update {

class UpdateManager : public QObject
{
    Q_OBJECT
public:
    UpdateManager();
    virtual ~UpdateManager();

    void check();

signals:
    void updateAvailable();
};

}

}

}
#endif // UPDATEMANAGER_HPP
