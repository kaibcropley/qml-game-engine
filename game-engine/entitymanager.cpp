#include "entitymanager.h"
#include <stdlib.h>
#include "pathfinder.h"

#include <QPoint>

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

    if (gridMatrix->rows() == 0) {
        srand (time(NULL));
        // FOR TESTING
        QVector<QVector<GridSquareData *>> *grid = new QVector<QVector<GridSquareData *>>;
        for(int i = 0; i < 10; i++) // Initialize starting with row by row
        {
            QVector<GridSquareData *> currRow;
            for(int x = 0; x < 10; x++)
            {
                GridSquareData *newSquare = new GridSquareData(0, QPoint(i, x));
                newSquare->setSquareType(static_cast<GridSquareData::BoardSquareType>((rand() % 2)));
                newSquare->setBlocked((rand() % 5) == 1);
                if (!newSquare->getBlocked()) {
                    newSquare->setContainsFood((rand() % 5) == 1);
                } else {
                    qDebug() << QPoint(i, x) << "is blocked";
                    newSquare->setContainsFood(false);
                }
                currRow.append(newSquare);
            }
            grid->append(currRow);
        }
        gridMatrix->setMatrix(grid);
    }

    targetEntity->setPath(PathFinder::getInstance()->findPath(gridMatrix, source, target));
    return targetEntity->pathHasSteps();
}
