#include "gridsquaredata.h"

GridSquareData::GridSquareData(QQuickItem *parent, QPoint gridPos) :
    QQuickItem(parent),
    m_gridPos(gridPos),
    m_squareType(DIRT),
    m_blocked(false),
    m_containsFood(false)
{
}

GridSquareData::GridSquareData(const GridSquareData &other)
{
    this->m_gridPos = other.m_gridPos;
    this->m_squareType = other.m_squareType;
    this->m_blocked = other.m_blocked;
    this->m_containsFood = other.m_containsFood;
}

//GridSquare:: GridSquare(QObject *parent, BoardSquareType boardSquareType) :
//    QObject(parent),
//    m_squareType(boardSquareType),
//    m_containsFood(false)
//{

//}

GridSquareData GridSquareData::operator=(const GridSquareData& other)
{
    this->setSquareType(other.getSquareType());
    this->setBlocked(other.getBlocked());
    this->setContainsFood(other.getContainsFood());

    return *this;
}

QVariantMap GridSquareData::toQVariantMap()
{
    QVariantMap vMap;
    vMap.insert("squareType", getSquareType());
    vMap.insert("blocked", getBlocked());
    vMap.insert("containsFood", getContainsFood());
    vMap.insert("gridPos", getGridPos());
    return vMap;
}

void GridSquareData::setSquareType(BoardSquareType newType)
{
    if (m_squareType != newType) {
        m_squareType = newType;
        emit onSquareTypeChanged(m_squareType);
    }
}

GridSquareData::BoardSquareType GridSquareData::getSquareType() const
{
    return m_squareType;
}

void GridSquareData::setBlocked(bool blocked)
{
    if (m_blocked != blocked) {
        m_blocked = blocked;
        emit onBlockedChanged(m_blocked);
    }
}

bool GridSquareData::getBlocked() const
{
    return m_blocked;
}

void GridSquareData::setContainsFood(bool containsFood)
{
    if (m_containsFood != containsFood) {
        m_containsFood = containsFood;
        emit onContainsFoodChanged(m_containsFood);
    }
}

bool GridSquareData::getContainsFood() const
{
    return m_containsFood;
}

void GridSquareData::setVisited(bool visited)
{
   m_visited = visited;
}

bool GridSquareData::getVisited()
{
    return m_visited;
}


QPoint GridSquareData::getGridPos()
{
    return m_gridPos;
}

void GridSquareData::setGridPos(QPoint pos)
{
    if (m_gridPos != pos) {
        m_gridPos = pos;
        emit onGridPosChanged(m_gridPos);
    }
}

int GridSquareData::getGridX()
{
    return m_gridPos.x();
}

void GridSquareData::setGridX(int newX)
{
    if (m_gridPos.x() != newX) {
        m_gridPos.setX(newX);
        emit onGridXChanged(newX);
    }
}

int GridSquareData::getGridY()
{
    return m_gridPos.y();
}

void GridSquareData::setGridY(int newY)
{
    if (m_gridPos.y() != newY) {
        m_gridPos.setY(newY);
        emit onGridYChanged(newY);
    }
}
