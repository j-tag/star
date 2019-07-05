#include "includes/star/Star.hpp"

#include <QSystemTrayIcon>
#include <QApplication>
#include <QAction>
#include <QMenu>
#include <QProcess>

star::tray::TrayIconManager::TrayIconManager() {}

star::tray::TrayIconManager::~TrayIconManager() {}

void star::tray::TrayIconManager::init()
{
    // Actions

    auto dateAction = new QAction("تاریخ: " + s.getJalaliDate()->getCurrentJalaliDayName() + " " + s.getJalaliDate()->getCurrentJalaliDate());

    auto starAction = new QAction("اجرای ستاره");

    connect(starAction, &QAction::triggered, this, &TrayIconManager::runStar);

    auto quitAction = new QAction("خروج");
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    // Menu
    auto trayIconMenu = new QMenu();
    trayIconMenu->addAction(dateAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(starAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    // Make tray icon
    this->pSystemTrayIcon = new QSystemTrayIcon(this);

    connect(this->pSystemTrayIcon, &QSystemTrayIcon::messageClicked, this, &TrayIconManager::runStar);

    // Assign menu items
    this->pSystemTrayIcon->setContextMenu(trayIconMenu);

    // Set icon
    this->pSystemTrayIcon->setIcon(QIcon(":/images/icon.png"));

    // Set hover tooltip
    this->pSystemTrayIcon->setToolTip("تقویم ستاره: " + s.getJalaliDate()->getCurrentJalaliDate());

    // Show tray icon
    this->pSystemTrayIcon->show();
}

void star::tray::TrayIconManager::showMessage(const QString &strTitle, const QString &strDescription, QSystemTrayIcon::MessageIcon icon)
{
    this->pSystemTrayIcon->showMessage(strTitle, strDescription, icon);
}

void star::tray::TrayIconManager::notifyTask(const QJsonObject &json)
{
    this->showMessage(json["title"].toString(), json["description"].toString());
}

void star::tray::TrayIconManager::runStar()
{
    QProcess::startDetached(s.getSettingsManager()->getStringValue("app/star_path"));
}

