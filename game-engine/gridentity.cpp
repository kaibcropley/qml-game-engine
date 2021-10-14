#include "gridentity.h"
#include <QtMath>
#include <QLinkedList>

// TODO REMOVE AFTER TEST CODE REMOVED


//GridEntity::GridEntity(QObject *parent) : QObject(parent)
//{

//}

GridEntity::GridEntity(QQuickItem *parent, int startX, int startY) :
    QQuickItem(parent),
    m_gridPos(QPoint(0, 0))
{
}

GridEntity::GridEntity(const GridEntity &other) :
    QQuickItem(0)
{
    this->m_gridPos = other.m_gridPos;
}

GridEntity GridEntity::operator=(const GridEntity& other)
{

    this->m_gridPos = other.m_gridPos;
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

int GridEntity::getGridX()
{
    return m_gridPos.x();
}

void GridEntity::setGridX(int newX)
{
    if (m_gridPos.x() != newX) {
        m_gridPos.setX(newX);
        emit onGridXChanged(newX);
    }
}

int GridEntity::getGridY()
{
    return m_gridPos.y();
}

void GridEntity::setGridY(int newY)
{
    if (m_gridPos.y() != newY) {
        m_gridPos.setY(newY);
        emit onGridYChanged(newY);
    }
}

void GridEntity::setPath(QVector<QPoint> path)
{
    m_Path = path;
}

// TODO remove return or give it a use
bool GridEntity::moveTo(QPoint target)
{
    setGridPos(target);
}

bool GridEntity::pathHasSteps()
{
    return m_Path.size() > 0;
}

void GridEntity::findPath(QPoint target)
{
    qDebug() << "TODO";
}

void GridEntity::followPath(int maxSteps)
{
    qDebug() << "GridEntity::followPath(" << maxSteps << ") Path length:" << m_Path.size();
    followPath(m_Path, maxSteps);
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

//bool GridEntity::step(MovementDirections direction)
//{
//    int newX = getGridX();
//    int newY = getGridY();

//    if (direction == MovementDirections::GRID_W || direction == MovementDirections::GRID_NW || direction == MovementDirections::GRID_SW) {
//        newX = newX - 1;
//    } else if (direction == MovementDirections::GRID_E || direction == MovementDirections::GRID_NE || direction == MovementDirections::GRID_SE) {
//        newX = newX + 1;
//    }

//    if (direction == MovementDirections::GRID_N || direction == MovementDirections::GRID_NE || direction == MovementDirections::GRID_NW) {
//        newY = newY - 1;
//    } else if (direction == MovementDirections::GRID_S || direction == MovementDirections::GRID_SE || direction == MovementDirections::GRID_SW) {
//        newY = newY + 1;
//    }

//    return moveTo(newX, newY);
//}
