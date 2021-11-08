#include "gridentity.h"
#include <QtMath>
#include <QLinkedList>
#include "pathfinder.h"

GridEntity::GridEntity(QQuickItem *parent) :
    QQuickItem(parent),
    m_gridPos(QPoint(0, 0)),
    m_movementEnabled(true),
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
    if (m_gridPos != pos && m_movementEnabled) {
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

bool GridEntity::getMovementEnabled()
{
    return m_movementEnabled;
}

void GridEntity::setMovementEnabled(bool enable)
{
    if (m_movementEnabled != enable) {
        m_movementEnabled = enable;
        emit onMovementEnabledChanged(m_movementEnabled);
    }
}

void GridEntity::setPath(QVector<QPoint> path)
{
    m_path = path;
}

void GridEntity::moveTo(QPoint target)
{
    setLastDirection(MovementEnums::getDirection(m_gridPos, target));
    setGridPos(target);
}

QPoint GridEntity::getPathStep(int pathStepIndex)
{
    return m_path.at(pathStepIndex);
}

QPoint GridEntity::getPathNextStep()
{
    return m_path.first();
}

QPoint GridEntity::getPathTarget()
{
    return m_path.last();
}

int GridEntity::pathLength()
{
    return m_path.size();
}

bool GridEntity::pathHasSteps()
{
    return pathLength() > 0;
}

// Finds and sets a path (m_path) on the current matrix (p_gridMatrix)
bool GridEntity::findPath(QPoint target)
{
    setPath(PathFinder::getInstance()->findPath(p_gridMatrix, getGridPos(), target, 1));
    return pathHasSteps();
}

bool GridEntity::followPath(int maxSteps)
{
    if (m_movementEnabled && pathHasSteps()) {
        if (maxSteps > 1) {
            return followPath(m_path, maxSteps);
        } else { // If just 1 step, do here for performance
            moveTo(m_path.at(0));
            m_path.removeFirst();
            return true;
        }
    }
    return false;
}

bool GridEntity::followPath(QVector<QPoint> &path, int maxSteps)
{
    if (m_movementEnabled && pathHasSteps()) {
        int currSteps = 0;
        QVectorIterator<QPoint> pathSteps(path);
        while (pathSteps.hasNext() && currSteps < maxSteps && pathHasSteps()) {
            moveTo(pathSteps.next());
            path.pop_front();
            currSteps++;
        }
        return true;
    }
    return false;
}
