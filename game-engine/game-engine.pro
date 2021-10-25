TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    physics-game/collisionmanager.cpp \
    grid-game/gameboard.cpp \
    grid-game/gridentity.cpp \
    grid-game/gridsquaredata.cpp \
    grid-game/gridentityfactory.cpp \
    grid-game/entitymanager.cpp \
    grid-game/gridmatrix.cpp \
    grid-game/pathfinder.cpp \
    grid-game/gridmatrixfactory.cpp \
    grid-game/movementenums.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    physics-game/collisionmanager.h \
    grid-game/gameboard.h \
    grid-game/gridentity.h \
    grid-game/gridsquaredata.h \
    grid-game/gridentityfactory.h \
    grid-game/entitymanager.h \
    grid-game/gridmatrix.h \
    grid-game/pathfinder.h \
    grid-game/gridmatrixfactory.h \
    grid-game/movementenums.h
