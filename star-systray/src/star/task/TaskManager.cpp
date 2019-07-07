#include "includes/star/Star.hpp"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTimer>

star::task::TaskManager::TaskManager() {

    connect(s.getOAuth2(), &star::web::auth::OAuth2::loginResult, this, &star::task::TaskManager::initWorker);
}

star::task::TaskManager::~TaskManager() {}

void star::task::TaskManager::initWorker(bool bStart)
{
    if(bStart == false) {
        // Failed to login to Pure account, so don't start worker
        qInfo() << Q_FUNC_INFO << ": Will not start task manager timer due to failed Pure account login result.";
        return;
    }

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&TaskManager::reload));
    timer->start(5 * 60 * 1000); // 5 Min
}

void star::task::TaskManager::reload()
{
    qInfo() << Q_FUNC_INFO << ": Reloading reminder tasks...";

    this->reloadDate();
    this->reloadTime();
    this->reloadDateTime();
}

void star::task::TaskManager::reloadDate()
{
    QString patternUrl("apps/fa/star-v4/task-reminder/date/$YEAR/$MONTH/$DAY.json?page=1");

    auto strUrl = patternUrl.replace("$YEAR", s.getJalaliDate()->getCurrentJalaliYear())
            .replace("$MONTH", s.getJalaliDate()->getCurrentJalaliMonth())
            .replace("$DAY", s.getJalaliDate()->getCurrentJalaliDayInMonth());

    this->findTasks(strUrl);
}

void star::task::TaskManager::reloadTime()
{
    QString patternUrl("apps/fa/star-v4/task-reminder/time/$HOUR/$MINUTE/$SECONDS.json?page=1");

    auto current = QTime::currentTime();

    auto strUrl = patternUrl.replace("$HOUR", QString::number(current.hour()))
            .replace("$MINUTE", QString::number(current.minute()))
            .replace("$SECONDS", QString::number(current.second()));

    this->findTasks(strUrl);
}

void star::task::TaskManager::reloadDateTime()
{
    QString patternUrl("apps/fa/star-v4/task-reminder/date-time/$YEAR/$MONTH/$DAY/$HOUR/$MINUTE/$SECONDS.json?page=1");

    auto current = QTime::currentTime();

    auto strUrl = patternUrl.replace("$YEAR", s.getJalaliDate()->getCurrentJalaliYear())
            .replace("$MONTH", s.getJalaliDate()->getCurrentJalaliMonth())
            .replace("$DAY", s.getJalaliDate()->getCurrentJalaliDayInMonth())
            .replace("$HOUR", QString::number(current.hour()))
            .replace("$MINUTE", QString::number(current.minute()))
            .replace("$SECONDS", QString::number(current.second()));

    this->findTasks(strUrl);
}

void star::task::TaskManager::findTasks(const QString &strUrl)
{
    s.getWebAccessManager()->withAuthenticationHeader()->get(s.getUrlManager()->getPureUrl(strUrl), [this](QNetworkReply *reply, int ) {
        // Read data
        auto jsoc = QJsonDocument::fromJson(reply->readAll());
        auto json = jsoc.array();

        // Tasks
        auto fetchedTasks = json.toVariantList();

        this->mutex.lock();

        // Edit item in local list if it is modified
        for (QVariantList::iterator j = fetchedTasks.begin(); j != fetchedTasks.end(); j++)
        {
            auto onlineJsob = (*j).toJsonObject();

            int i = 0;
            bool founded = false;

            for (QVariantList::iterator l = this->_varLstTasks.begin(); l != this->_varLstTasks.end(); l++)
            {
                auto localJsob = (*l).toJsonObject();

                if(onlineJsob["id"].toInt() == localJsob["id"].toInt()) {

                    founded = true;

                    if(onlineJsob["updated_at"].toInt() != localJsob["updated_at"].toInt()) {
                        // Task is changed

                        // Notify task
                        s.getTrayIconManager()->notifyTask(onlineJsob);

                        // Update in local list
                        this->_varLstTasks.replace(i, onlineJsob);

                        break;
                    }

                    break;
                }

                ++i;
            }

            // If item was not in list before, we can add it and notify it
            if(founded == false) {
                // Notify task
                s.getTrayIconManager()->notifyTask(onlineJsob);

                // Add to local list
                this->_varLstTasks.append(onlineJsob);
            }

        }

        this->mutex.unlock();
    });
}

QVariantList star::task::TaskManager::getTasks() const
{
    return this->_varLstTasks;
}
