#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>

#include "collisionmanager.h"
#include "gameboard.h"
#include "gridsquaredata.h"
#include "gridentity.h"
#include "gridentityfactory.h"
#include "entitymanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Register C++ items in QML
    qmlRegisterType<GridSquareData>("kcropley.grid", 1, 0, "GridSquareData");
    qmlRegisterType<GridEntity>("kcropley.grid", 1, 0, "GridEntity");

    // Set C++ context in QML
//    GridEntityFactory gridEntityFactory;
    CollisionManager collisionManager;
    GameBoard gameBoard;
    EntityManager entityManager(0, &gameBoard);
//    engine.rootContext()->setContextProperty("gridEntityFactory", &gridEntityFactory);
    engine.rootContext()->setContextProperty("collisionManager", &collisionManager);
    engine.rootContext()->setContextProperty("gameBoard", &gameBoard);
    engine.rootContext()->setContextProperty("entityManager", &entityManager);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
