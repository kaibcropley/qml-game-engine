#include "gridsquare.h"

GridSquare::GridSquare(QObject *parent) :
    QObject(parent),
    m_squareType(DIRT),
    m_containsFood(false)
{

}

GridSquare::GridSquare(const GridSquare &other)
{
    this->setSquareType(other.getSquareType());
}

//GridSquare:: GridSquare(QObject *parent, BoardSquareType boardSquareType) :
//    QObject(parent),
//    m_squareType(boardSquareType),
//    m_containsFood(false)
//{

//}

GridSquare operator=(const GridSquare&)
{
    GridSquare newSquare;
    newSquare.setSquareType(this.getSquareType());
    return newSquare;
}

void GridSquare::setSquareType(BoardSquareType newType)
{
    m_squareType = newType;
    emit onSquareTypeChanged(newType);
}

GridSquare::BoardSquareType GridSquare::getSquareType() const
{
    return m_squareType;
}
