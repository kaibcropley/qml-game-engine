#include "entitymanager.h"
#include <stdlib.h>
#include "pathfinder.h"

#include <QPoint>

#include "gridsquaredata.h"

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

GridEntity * EntityManager::checkForEntityCollision(GridEntity *entity)
{
    QVectorIterator<GridEntity *> entitiesItr(entities);
    while (entitiesItr.hasNext()) {
        GridEntity *curr = entitiesItr.next();
        if (curr != entity) {
            if (curr->getGridPos() == entity->getGridPos()) {
                return curr;
            }
        }
    }
    return nullptr;
}

