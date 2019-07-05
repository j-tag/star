#ifndef TASKMANAGER_HPP
#define TASKMANAGER_HPP

#include <QMutex>
#include <QObject>
#include <QVariantList>

namespace star {

namespace task {

class TaskManager : public QObject
{
public:

    Q_OBJECT
public:
    TaskManager();
    virtual ~TaskManager();

    QVariantList getTasks() const;

public slots:
    void initWorker(bool bStart);
    void reload();

private:
    void reloadDate();
    void reloadTime();
    void reloadDateTime();
    void findTasks(const QString &strUrl);

    QVariantList _varLstTasks;
    QMutex mutex;
};

}

}

#endif // TASKMANAGER_HPP
