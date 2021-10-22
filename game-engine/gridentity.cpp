#include "gridentity.h"
#include <QtMath>
#include <QLinkedList>
#include "pathfinder.h"

GridEntity::GridEntity(QQuickItem *parent) :
    QQuickItem(parent),
    m_gridPos(QPoint(0, 0)),
    m_lastDirection(MovementEnums::North)
{
}

GridEntity::GridEntity(const GridEntity &other) :
    QQuickItem(0)
{
    this->m_gridPos = other.m_gridPos;
    this->p_gridMatrix = other.p_gridMatrix;
}

GridEntity GridEntity::operator=(const GridEntity& other)
{

    this->m_gridPos = other.m_gridPos;
    this->p_gridMatrix = other.p_gridMatrix;
    return *this;
}

QPoint GridEntity::getGridPos()
{
    return m_gridPos;
}

void GridEntity::setGridPos(QPoint pos)
{
    if (m_gridPos != pos) {
        m_gridPos = pos;
        emit onGridPosChanged(m_gridPos);
    }
}

GridMatrix * GridEntity::getGridMatrix()
{
    return p_gridMatrix;
}

void GridEntity::setGridMatrix(GridMatrix *newGridMatrix)
{
    p_gridMatrix = newGridMatrix;
    emit onGridMatrixChanged(p_gridMatrix);
}

MovementEnums::Directions GridEntity::getLastDirection()
{
    return m_lastDirection;
}

void GridEntity::setLastDirection(MovementEnums::Directions newDirection)
{
    m_lastDirection = newDirection;
    emit onLastDirectionChanged(m_lastDirection);
}

void GridEntity::setPath(QVector<QPoint> path)
{
    m_Path = path;
}

void GridEntity::moveTo(QPoint target)
{
    setLastDirection(MovementEnums::getDirection(m_gridPos, target));
    setGridPos(target);
}

bool GridEntity::pathHasSteps()
{
    return m_Path.size() > 0;
}

void GridEntity::findPath(QPoint target)
{
    setPath(PathFinder::getInstance()->findPath(p_gridMatrix, getGridPos(), target));
}

void GridEntity::followPath(int maxSteps)
{
//    qDebug() << "GridEntity::followPath(" << maxSteps << ") Path length:" << m_Path.size();
    if (pathHasSteps()) {
        if (maxSteps > 1) {
            followPath(m_Path, maxSteps);
        } else { // If just 1 step, do here for performance
            moveTo(m_Path.at(0));
            m_Path.removeFirst();
        }
    }
}

void GridEntity::followPath(QVector<QPoint> &path, int maxSteps)
{
    int currSteps = 0;
    QVectorIterator<QPoint> pathSteps(path);
    while (pathSteps.hasNext() && currSteps < maxSteps && pathHasSteps()) {
        moveTo(pathSteps.next());
        path.pop_front();
        currSteps++;
    }
}


