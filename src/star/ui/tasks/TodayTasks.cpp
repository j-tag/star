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

        // Success

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

        // Fail

        // Populate changes
        emit this->deleteTaskResult(id, false);
    });
}

void star::ui::tasks::TodayTasks::editTask(int id, const QString &strTitle, const QString &strDescription, int triggerDate, const QString &strTriggerTime)
{
    QString patternUrl("apps/fa/star-v3/tasks/%ID.json");

    auto strUrl = patternUrl.replace("%ID", QString::number(id));

    // Generate JSON request body
    QJsonObject json = QJsonObject();
    QJsonDocument jsoc = QJsonDocument();

    json["title"] = strTitle;

    if(strDescription.trimmed().length() > 0) {
        json["description"] = strDescription.trimmed();
    } else {
        json["description"] = QJsonValue(QJsonValue::Null);
    }

    if(triggerDate != -1) {
        json["trigger_date"] = triggerDate;
    } else {
        json["trigger_date"] = QJsonValue(QJsonValue::Null);
    }

    if(strTriggerTime.trimmed().length() > 0) {
        json["trigger_time"] = strTriggerTime;
    } else {
        json["trigger_time"] = QJsonValue(QJsonValue::Null);
    }


    jsoc.setObject(json);

    QString strBody = jsoc.toJson();

    s.getWebAccessManager()->withAuthenticationHeader()->put(s.getUrlManager()->getPureUrl(strUrl), strBody, [=](QNetworkReply *reply, int ) {

        // Success

        auto json = QJsonDocument::fromJson(reply->readAll()).object();

        int i = 0;
        // Edit item in local list
        for (QVariantList::iterator j = this->_varLstTasks.begin(); j != this->_varLstTasks.end(); j++)
        {
            if((*j).toJsonObject()["id"].toInt() == id) {
                this->_varLstTasks.replace(i, json);
                break;
            }

            ++i;
        }

        // Populate changes
        emit this->tasksChanged(this->_varLstTasks);
        emit this->editTaskResult(id, true);
    }, [=](QNetworkReply *, int ) {

        // Fail

        // Populate changes
        emit this->editTaskResult(id, false);
    });
}

void star::ui::tasks::TodayTasks::createTask(const QString &strTitle, const QString &strDescription, int triggerDate, const QString &strTriggerTime)
{
    QString strUrl("apps/fa/star-v3/tasks.json");

    // Generate JSON request body
    QJsonObject json = QJsonObject();
    QJsonDocument jsoc = QJsonDocument();

    json["title"] = strTitle;

    if(strDescription.trimmed().length() > 0) {
        json["description"] = strDescription.trimmed();
    } else {
        json["description"] = QJsonValue(QJsonValue::Null);
    }

    if(triggerDate != -1) {
        json["trigger_date"] = triggerDate;
    } else {
        json["trigger_date"] = QJsonValue(QJsonValue::Null);
    }

    if(strTriggerTime.trimmed().length() > 0) {
        json["trigger_time"] = strTriggerTime;
    } else {
        json["trigger_time"] = QJsonValue(QJsonValue::Null);
    }


    jsoc.setObject(json);

    QString strBody = jsoc.toJson();

    s.getWebAccessManager()->withAuthenticationHeader()->post(s.getUrlManager()->getPureUrl(strUrl), strBody, [=](QNetworkReply *reply, int ) {

        // Success

        auto json = QJsonDocument::fromJson(reply->readAll()).object();

        this->_varLstTasks.prepend(json);

        // Populate changes
        emit this->tasksChanged(this->_varLstTasks);
        emit this->createTaskResult(true);
    }, [=](QNetworkReply *, int ) {

        // Fail

        // Populate changes
        emit this->createTaskResult(false);
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

