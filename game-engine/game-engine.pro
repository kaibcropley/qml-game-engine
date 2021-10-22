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
    gridmatrix.cpp \
    pathfinder.cpp \
    gridmatrixfactory.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    collisionmanager.h \
    gameboard.h \
    gridentity.h \
    gridsquaredata.h \
    gridentityfactory.h \
    entitymanager.h \
    gridmatrix.h \
    pathfinder.h \
    gridmatrixfactory.h
