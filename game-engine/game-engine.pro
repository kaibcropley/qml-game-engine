TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    collisionmanager.cpp \
    gameboard.cpp \
    gridsquare.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    collisionmanager.h \
    gameboard.h \
    gridsquare.h
