#include "includes/star/Star.hpp"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

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

        // Pagination
        this->_nPageCount = reply->rawHeader("X-Pagination-Page-Count").toInt();
        this->_nCurrentPage = reply->rawHeader("X-Pagination-Current-Page").toInt();

        // Populate changes
        emit this->tasksChanged(this->_varLstTasks);
        emit this->paginationChanged(this->_nPageCount, this->_nCurrentPage);
    });
}

void star::ui::tasks::TodayTasks::append(int page)
{
    QString patternUrl("apps/fa/star-v3/tasks.json?page=%PAGE");

    auto strUrl = patternUrl.replace("%PAGE", QString::number(page));

    s.getWebAccessManager()->withAuthenticationHeader()->get(s.getUrlManager()->getPureUrl(strUrl), [=](QNetworkReply *reply, int ) {
        // Read data
        auto jsoc = QJsonDocument::fromJson(reply->readAll());
        auto json = jsoc.array();

        // Tasks
        this->_varLstTasks += json.toVariantList();

        // Pagination
        this->_nPageCount = reply->rawHeader("X-Pagination-Page-Count").toInt();
        this->_nCurrentPage = reply->rawHeader("X-Pagination-Current-Page").toInt();

        // Populate changes
        emit this->tasksChanged(this->_varLstTasks);
        emit this->paginationChanged(this->_nPageCount, this->_nCurrentPage);
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

        // Delete item from local list
        for (QVariantList::iterator j = this->_varLstTasks.begin(); j != this->_varLstTasks.end(); j++)
        {
            if((*j).toJsonObject()["id"].toInt() == id) {
                this->_varLstTasks.erase(j);
                break;
            }
        }

        // Populate changes
        emit this->tasksChanged(this->_varLstTasks);
        emit this->deleteTaskResult(id, true);
    }, [=](QNetworkReply *, int ) {
        // Populate changes
        emit this->deleteTaskResult(id, false);
    });
}

int star::ui::tasks::TodayTasks::getPageCount()
{
    return this->_nPageCount;
}

int star::ui::tasks::TodayTasks::getCurrentPage()
{
    return this->_nCurrentPage;
}

