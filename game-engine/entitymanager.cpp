#include "entitymanager.h"

EntityManager::EntityManager(QObject *parent, GameBoard *incomingGameBoard) :
    QObject(parent),
//    target(nullptr),
    gameBoard(incomingGameBoard)
{

}

void EntityManager::registerEntity(GridEntity *entity)
{
    qDebug() << "registerEntity" << entity->getName();
    m_entities.append(entity);
}

void EntityManager::updateEntities()
{
    QVectorIterator<GridEntity *> entitiesItr(m_entities);
    while (entitiesItr.hasNext()) {
        qDebug() << entitiesItr.next();
    }
}

void EntityManager::findPath(int targetX, int targetY)
{
    if (m_entities.size() == 0 || gameBoard == nullptr) {
        qDebug() << "EntityManager::findPath" << "Found nullptr";
        return;
    }

    QVectorIterator<GridEntity *> entitiesItr(m_entities);
    while (entitiesItr.hasNext()) {
        qDebug() << entitiesItr.next();
    }
}
