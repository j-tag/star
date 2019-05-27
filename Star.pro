TEMPLATE = app

QT += qml quick quickcontrols2 widgets network

SOURCES += src/main.cpp \
    src/star/date/CJalaliDate.cpp \
    src/star/web/WebAccessManager.cpp \
    src/star/web/auth/OAuth2.cpp \
    src/star/Star.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

HEADERS += \
    includes/star/date/CJalaliDate.hpp \
    includes/star/web/auth/OAuth2.hpp \
    includes/star/Star.hpp \
    includes/star/web/WebAccessManager.hpp
