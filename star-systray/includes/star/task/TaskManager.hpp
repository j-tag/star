#ifndef TASKMANAGER_HPP
#define TASKMANAGER_HPP

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

signals:
    void tasksChanged(QVariantList tasks);
    void paginationChanged(int pageCount, int currentPage);

public slots:
    void reload(int page = 1);
    void append(int page = 1);
    QVariantList getTasks() const;
    int getPageCount();
    int getCurrentPage();

private:
    QVariantList _varLstTasks;
    int _nPageCount;
    int _nCurrentPage;
};

}

}

#endif // TASKMANAGER_HPP
