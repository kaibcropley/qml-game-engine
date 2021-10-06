#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "collisionmanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Set C++ context in QML
    CollisionManager collisionManager;
    engine.rootContext()->setContextProperty("collisionManager", &collisionManager);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
