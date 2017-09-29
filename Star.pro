TEMPLATE = app

QT += qml quick quickcontrols2 widgets

SOURCES += main.cpp \
    CJalaliDate.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    CJalaliDate.h
