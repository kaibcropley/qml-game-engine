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
#include "gridmatrix.h"

#include "gridmatrixfactory.h"

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

    GridMatrixFactory factory;
    GridMatrix *gridMatrix = factory.createRandomMatrix(10, 10);
    EntityManager entityManager(0, gridMatrix);
//    engine.rootContext()->setContextProperty("gridEntityFactory", &gridEntityFactory);
    engine.rootContext()->setContextProperty("collisionManager", &collisionManager);
    engine.rootContext()->setContextProperty("gameBoard", &gameBoard);
    engine.rootContext()->setContextProperty("entityManager", &entityManager);
    engine.rootContext()->setContextProperty("gridMatrix", gridMatrix);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
