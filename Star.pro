TEMPLATE = app

QT += qml quick quickcontrols2 widgets

SOURCES += main.cpp \
    src/date/CJalaliDate.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

HEADERS += \
    includes/date/CJalaliDate.h
