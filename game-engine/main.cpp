#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>

#include "physics-game/collisionmanager.h"
#include "grid-game/gameboard.h"
#include "grid-game/gridsquaredata.h"
#include "grid-game/gridentity.h"
#include "grid-game/gridentityfactory.h"
#include "grid-game/entitymanager.h"
#include "grid-game/gridmatrix.h"

#include "grid-game/gridmatrixfactory.h"

#include "grid-game/gridgamemanager.h"

#include "physics-game/circlecollider.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Register C++ items in QML
    qmlRegisterType<GridSquareData>("kcropley.grid", 1, 0, "GridSquareData");
    qmlRegisterType<GridEntity>("kcropley.grid", 1, 0, "GridEntity");
    qmlRegisterType<CircleCollider>("kcropley.physics", 1, 0, "CircleCollider");

    GridGameManager gm;
    gm.initializeGridGame(10, 10);

    // Set C++ context in QML
//    GridEntityFactory gridEntityFactory;
    CollisionManager collisionManager;

//    GridMatrixFactory factory;
    GridMatrix *gridMatrix = new GridMatrix(0, 100, 100); //= //factory.createRandomMatrix(10, 10);
    EntityManager entityManager(0, gridMatrix);
//    engine.rootContext()->setContextProperty("gridEntityFactory", &gridEntityFactory);
    engine.rootContext()->setContextProperty("collisionManager", &collisionManager);
    engine.rootContext()->setContextProperty("entityManager", &entityManager);
    engine.rootContext()->setContextProperty("gridMatrix", gridMatrix);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
