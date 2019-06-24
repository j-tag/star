#include "includes/star/Star.hpp"

#include <QJsonDocument>
#include <QJsonArray>

star::ui::tasks::TodayTasks::TodayTasks() {}

star::ui::tasks::TodayTasks::~TodayTasks() {}

void star::ui::tasks::TodayTasks::reload(int page)
{
    QString patternUrl("apps/fa/star-v3/tasks.json?page=%PAGE");

    auto strUrl = patternUrl.replace("%PAGE", QString::number(page));

    s.getWebAccessManager()->withAuthenticationHeader()->get(s.getUrlManager()->getPureUrl(strUrl), [=](QNetworkReply *reply, int ) {
        // Read data
        auto jsoc = QJsonDocument::fromJson(reply->readAll());
        auto json = jsoc.array();

        // Tasks
        this->_varLstTasks = json.toVariantList();

        // Populate changes
        emit this->tasksChanged(this->_varLstTasks);
    });
}

QVariantList star::ui::tasks::TodayTasks::getTasks() const
{
    return this->_varLstTasks;
}

void star::ui::tasks::TodayTasks::deleteTask(int id)
{
    QString patternUrl("apps/fa/star-v3/tasks/%ID.json");

    auto strUrl = patternUrl.replace("%ID", QString::number(id));

    s.getWebAccessManager()->withAuthenticationHeader()->deleteResource(s.getUrlManager()->getPureUrl(strUrl), [=](QNetworkReply *, int ) {
        // Populate changes
        emit this->deleteTaskResult(id, true);
    }, [=](QNetworkReply *, int ) {
        // Populate changes
        emit this->deleteTaskResult(id, false);
    });
}
