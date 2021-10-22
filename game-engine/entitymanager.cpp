#include "entitymanager.h"
#include <stdlib.h>
#include "pathfinder.h"

#include <QPoint>

EntityManager::EntityManager(QObject *parent, GridMatrix *incomingGridMatrix) :
    QObject(parent),
    m_gridMatrix(incomingGridMatrix),
    entities()
{

}

bool EntityManager::registerEntity(GridEntity *entity)
{
    entities.append(entity);
    entity->setGridMatrix(m_gridMatrix);
}

void EntityManager::updateEntities()
{
//    targetEntity->followPath(1);
}

