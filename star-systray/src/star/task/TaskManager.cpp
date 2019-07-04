#include "includes/star/Star.hpp"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

star::task::TaskManager::TaskManager() {}

star::task::TaskManager::~TaskManager() {}

void star::task::TaskManager::reload(int page)
{
    QString patternUrl("apps/fa/star-v3/tasks.json?page=%PAGE");

    auto strUrl = patternUrl.replace("%PAGE", QString::number(page));

    s.getWebAccessManager()->withAuthenticationHeader()->get(s.getUrlManager()->getPureUrl(strUrl), [this](QNetworkReply *reply, int ) {
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

void star::task::TaskManager::append(int page)
{
    QString patternUrl("apps/fa/star-v3/tasks.json?page=%PAGE");

    auto strUrl = patternUrl.replace("%PAGE", QString::number(page));

    s.getWebAccessManager()->withAuthenticationHeader()->get(s.getUrlManager()->getPureUrl(strUrl), [this](QNetworkReply *reply, int ) {
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

QVariantList star::task::TaskManager::getTasks() const
{
    return this->_varLstTasks;
}

int star::task::TaskManager::getPageCount()
{
    return this->_nPageCount;
}

int star::task::TaskManager::getCurrentPage()
{
    return this->_nCurrentPage;
}

