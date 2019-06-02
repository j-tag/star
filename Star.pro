TEMPLATE = app

QT += qml quick quickcontrols2 widgets network

SOURCES += src/main.cpp \
    src/star/date/CJalaliDate.cpp \
    src/star/settings/SettingsManager.cpp \
    src/star/ui/general/Alerts.cpp \
    src/star/ui/home/UserDetails.cpp \
    src/star/ui/setup/SetupWizard.cpp \
    src/star/web/WebAccessManager.cpp \
    src/star/web/auth/OAuth2.cpp \
    src/star/Star.cpp \
    src/star/web/url/UrlManager.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

HEADERS += \
    includes/star/date/CJalaliDate.hpp \
    includes/star/settings/SettingsManager.hpp \
    includes/star/ui/general/Alerts.hpp \
    includes/star/ui/home/UserDetails.hpp \
    includes/star/ui/setup/SetupWizard.hpp \
    includes/star/web/auth/ApiToken.hpp \
    includes/star/web/auth/OAuth2.hpp \
    includes/star/Star.hpp \
    includes/star/web/WebAccessManager.hpp \
    includes/star/web/url/UrlManager.hpp
