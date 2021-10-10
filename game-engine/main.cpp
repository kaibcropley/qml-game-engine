#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>

#include "collisionmanager.h"
#include "gameboard.h"
#include "gridsquare.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Register C++ items in QML
    qmlRegisterType<GridSquare>("kcropley.gridsquare", 1, 0, "GridSquare");

    // Set C++ context in QML
    CollisionManager collisionManager;
    GameBoard gameBoard;
    engine.rootContext()->setContextProperty("collisionManager", &collisionManager);
    engine.rootContext()->setContextProperty("gameBoard", &gameBoard);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
