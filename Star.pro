TEMPLATE = app

QT += qml quick quickcontrols2 widgets network

SOURCES += src/main.cpp \
    src/star/date/CJalaliDate.cpp \
    src/star/date/HijriDate.cpp \
    src/star/date/HijriDateCalculator.cpp \
    src/star/date/events/TodayEvents.cpp \
    src/star/settings/SettingsManager.cpp \
    src/star/ui/general/Alerts.cpp \
    src/star/ui/home/UserDetails.cpp \
    src/star/ui/setup/SetupWizard.cpp \
    src/star/ui/tasks/TodayTasks.cpp \
    src/star/web/WebAccessManager.cpp \
    src/star/web/auth/OAuth2.cpp \
    src/star/Star.cpp \
    src/star/web/update/UpdateManager.cpp \
    src/star/web/url/UrlManager.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

HEADERS += \
    includes/star/date/CJalaliDate.hpp \
    includes/star/date/HijriDateCalculator.hpp \
    includes/star/date/events/TodayEvents.hpp \
    includes/star/settings/SettingsManager.hpp \
    includes/star/ui/general/Alerts.hpp \
    includes/star/ui/home/UserDetails.hpp \
    includes/star/ui/setup/SetupWizard.hpp \
    includes/star/ui/tasks/TodayTasks.hpp \
    includes/star/web/auth/ApiToken.hpp \
    includes/star/web/auth/OAuth2.hpp \
    includes/star/Star.hpp \
    includes/star/web/WebAccessManager.hpp \
    includes/star/web/update/UpdateManager.hpp \
    includes/star/web/url/UrlManager.hpp \
    includes/star/date/HijriDate.hpp


VERSION = 4.0.0
VERSION_MAJOR = 4
VERSION_MINOR = 0
VERSION_REVISION = 0
VERSION_NUMBER = $$VERSION_MAJOR$$VERSION_MINOR$$VERSION_REVISION

DEFINES += VERSION=\\\"$$VERSION\\\"
DEFINES += VERSION_MAJOR=$$VERSION_MAJOR
DEFINES += VERSION_MINOR=$$VERSION_MINOR
DEFINES += VERSION_REVISION=$$VERSION_REVISION
DEFINES += VERSION_NUMBER=$$VERSION_NUMBER

QMAKE_TARGET_COMPANY = Pure Soft
QMAKE_TARGET_PRODUCT = Star Persian Calendar
QMAKE_TARGET_DESCRIPTION = Star Persian calendar and note manager
QMAKE_TARGET_COPYRIGHT = CopyRight (C) 2012 - 2019 . AllRights Reserved by Pure Soft


RC_ICONS = star.ico
