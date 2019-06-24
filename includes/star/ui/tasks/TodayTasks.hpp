#ifndef TODAYTASKS_HPP
#define TODAYTASKS_HPP

#include <QObject>
#include <QVariantList>

namespace star {

namespace ui {

namespace tasks {

class TodayTasks : public QObject
{
public:
    Q_PROPERTY(QVariantList tasks READ getTasks NOTIFY tasksChanged)
    Q_PROPERTY(int pageCount READ getPageCount NOTIFY paginationChanged)
    Q_PROPERTY(int currentPage READ getCurrentPage NOTIFY paginationChanged)

    Q_OBJECT
public:
    TodayTasks();
    virtual ~TodayTasks();

signals:
    void tasksChanged(QVariantList tasks);
    void deleteTaskResult(int id, bool result);
    void paginationChanged(int pageCount, int currentPage);

public slots:
    void reload(int page = 1);
    void append(int page = 1);
    QVariantList getTasks() const;
    void deleteTask(int id);
    int getPageCount();
    int getCurrentPage();

private:
    QVariantList _varLstTasks;
    int _nPageCount;
    int _nCurrentPage;
};

}

}

}

#endif // TODAYTASKS_HPP
