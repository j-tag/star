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

    Q_OBJECT
public:
    TodayTasks();
    virtual ~TodayTasks();

signals:
    void tasksChanged(QVariantList tasks);

public slots:
    void reload(int page = 1);
    QVariantList getTasks() const;

private:
    QVariantList _varLstTasks;
};

}

}

}

#endif // TODAYTASKS_HPP
