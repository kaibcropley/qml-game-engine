#include "entitymanager.h"
#include "pathfinder.h"

EntityManager::EntityManager(QObject *parent, GridMatrix *incomingGridMatrix) :
    QObject(parent),
    targetEntity(nullptr),
    gridMatrix(incomingGridMatrix)
{

}

bool EntityManager::registerEntity(GridEntity *entity)
{
    targetEntity = entity;
}

void EntityManager::updateEntities()
{
    targetEntity->followPath(1);
}

bool EntityManager::findPath(QPoint target)
{
    findPath(targetEntity->getGridPos(), target);
}

bool EntityManager::findPath(QPoint source, QPoint target)
{
    if (gridMatrix == nullptr) {
        qDebug() << "EntityManager::findPath" << "Found nullptr";
        return false;
    }

    // FOR TESTING
    QVector<QVector<GridSquareData *>> grid;
    for(int i = 0; i < 10; i++) // Initialize starting with row by row
    {
        QVector<GridSquareData *> currRow;
        for(int x = 0; x < 10; x++) // Initialize starting with
        {
            GridSquareData *newSquare = new GridSquareData;
            newSquare->setSquareType(static_cast<GridSquareData::BoardSquareType>(0)); // (getRandomInt() % 2));
            newSquare->setBlocked(false); // (getRandomInt() % 8) == 1);
            if (!newSquare->getBlocked()) {
                newSquare->setContainsFood(false); // (getRandomInt() % 5) == 1);
            } else {
                newSquare->setContainsFood(false);
            }
            currRow.append(newSquare);
        }
        grid.append(currRow);
    }
    gridMatrix->setMatrix(grid);

    targetEntity->setPath(PathFinder::getInstance()->findPath(gridMatrix, source, target));
    return targetEntity->pathHasSteps();
}
