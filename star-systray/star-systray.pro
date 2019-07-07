#-------------------------------------------------
#
# Project created by QtCreator 2019-07-03T12:14:01
#
#-------------------------------------------------

QT       += core network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = star-systray
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        src/main.cpp \
        src/star/Star.cpp \
        src/star/client/TcpClient.cpp \
        src/star/date/CjalaliDate.cpp \
        src/star/server/TcpServer.cpp \
        src/star/settings/SettingsManager.cpp \
        src/star/task/TaskManager.cpp \
        src/star/tray/TrayIconManager.cpp \
        src/star/user/BirthdayChecker.cpp \
        src/star/user/UserDetails.cpp \
        src/star/web/WebAccessManager.cpp \
        src/star/web/auth/OAuth2.cpp \
        src/star/web/url/UrlManager.cpp

HEADERS += \
    includes/star/Star.hpp \
    includes/star/client/TcpClient.hpp \
    includes/star/date/CJalaliDate.hpp \
    includes/star/server/TcpServer.hpp \
    includes/star/settings/SettingsManager.hpp \
    includes/star/task/TaskManager.hpp \
    includes/star/tray/TrayIconManager.hpp \
    includes/star/user/BirthdayChecker.hpp \
    includes/star/web/auth/ApiToken.hpp \
    includes/star/web/auth/OAuth2.hpp \
    includes/star/web/WebAccessManager.hpp \
    includes/star/web/url/UrlManager.hpp \
    includes/star/user/UserDetails.hpp

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    main.qrc

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
