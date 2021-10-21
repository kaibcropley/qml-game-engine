TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    collisionmanager.cpp \
    gameboard.cpp \
    gridentity.cpp \
    gridsquaredata.cpp \
    gridentityfactory.cpp \
    entitymanager.cpp \
    movementenums.cpp \
    bugai.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    collisionmanager.h \
    gameboard.h \
    gridsquaremodel.h \
    movementmanager.h \
    gridentity.h \
    gridsquaredata.h \
    gridentityfactory.h \
    entitymanager.h \
    movementenums.h \
    bugai.h
