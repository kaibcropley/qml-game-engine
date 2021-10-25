#include "gameboard.h"
#include <QTime>
#include <QDebug>

GameBoard::GameBoard(QObject *parent) : QObject(parent)
{

}

void GameBoard::getType(QObject *ptr)
{
//    qDebug() << ptr->
//    ptr->add("test");
}

void GameBoard::setGameBoard(QVector<QVector<GridSquareData *>> newBoard)
{
    m_gameBoard = newBoard;
}

QVector<QVector<GridSquareData *>> GameBoard::getGameBoard()
{
    return m_gameBoard;
}

GridSquareData* GameBoard::at(int x, int y)
{
    return getSquare(x, y);
}

GridSquareData* GameBoard::getSquare(int x, int y)
{
    return (m_gameBoard.at(x).at(y));
}

// Returns a QVariantMap/JSON obj with data for the UI
QVariantMap GameBoard::getSquareMap(int x, int y)
{
    return (m_gameBoard.at(x).at(y))->toQVariantMap();
}

// Returns an array of QVariantMap/JSON objects as one long array for the grid repeater
QVariant GameBoard::gameBoardToOneDimension()
{
    QVariantList oneDimensionalBoard;
    for(int y = 0; y < m_gameBoard.size(); y++)
    {
        for(int x = 0; x < m_gameBoard.at(y).size(); x++)
        {
            oneDimensionalBoard.append(getSquareMap(x, y));
        }
    }
    return QVariant::fromValue(oneDimensionalBoard);
}

void GameBoard::createRandomizedGameBoard(int height, int width)
{
    m_gameBoard = QVector<QVector<GridSquareData *>>();
    for(int i = 0; i < height; i++) // Initialize starting with row by row
    {
        QVector<GridSquareData *> currRow;
        for(int x = 0; x < width; x++) // Initialize starting with
        {
            GridSquareData *newSquare = new GridSquareData();
            newSquare->setSquareType("dirt");
            newSquare->setMovementAllowed((getRandomInt() % 8) == 1);
            if (!newSquare->getMovementAllowed()) {
                newSquare->setContainsFood((getRandomInt() % 5) == 1);
            } else {
                newSquare->setContainsFood(false);
            }
            currRow.append(newSquare);
        }
        m_gameBoard.append(currRow);
    }
}

int GameBoard::getRandomInt()
{
    return qrand();
}
