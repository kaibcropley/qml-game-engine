#include "entitymanager.h"

EntityManager::EntityManager(QObject *parent, GameBoard *incomingGameBoard) :
    QObject(parent),
    target(nullptr),
    gameBoard(incomingGameBoard)
{

}

bool EntityManager::registerEntity(GridEntity *entity)
{
    qDebug() << "registerEntity";
    target = entity;
}

void EntityManager::updateEntities()
{
    target->followPath(1);
}

void EntityManager::findPath(int targetX, int targetY)
{
    if (target == nullptr || gameBoard == nullptr) {
        qDebug() << "EntityManager::findPath" << "Found nullptr";
        return;
    }
//    qDebug() << "EntityManager::findPath(" << targetX << "," << targetY << ")";
    target->findPath(gameBoard->getGameBoard(), targetX, targetY);
}
