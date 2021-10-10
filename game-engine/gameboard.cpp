#include "gameboard.h"
#include <QDebug>

GameBoard::GameBoard(QObject *parent) : QObject(parent)
{

}

void GameBoard::setGameBoard(QVector<QVector<GridSquare *>> newBoard)
{
    m_gameBoard = newBoard;
}

QVector<QVector<GridSquare *>> GameBoard::gameBoard()
{
    return m_gameBoard;
}

// Expected that all rows are equal size
GridSquare * GameBoard::gameBoardToOneDimension()
{
    int currentOneDimensionalIndex = 0;
    int oneDimensionalSize = m_gameBoard.size() * m_gameBoard.at(0).size(); // All rows are equal size requirement
    GridSquare oneDimensionalBoard[oneDimensionalSize];
    for(int i = 0; i < m_gameBoard.size(); i++)
    {
        for(int x = 0; x < m_gameBoard.at(i).size(); x++) // Initialize starting with
        {
            oneDimensionalBoard[currentOneDimensionalIndex] = *(m_gameBoard.at(i).at(x));
            currentOneDimensionalIndex++;
        }
    }
    return oneDimensionalBoard;

//    QVector<GridSquare> oneDimensionalBoard;
//    for(int i = 0; i < m_gameBoard.size(); i++)
//    {
//        for(int i = 0; i < m_gameBoard.at(i).size(); i++) // Initialize starting with
//        {
//            qDebug() << m_gameBoard.at(i).at(i);
////            oneDimensionalBoard.append(m_gameBoard.at(i).at(i));
//        }
//    }
////    qDebug() << oneDimensionalBoard;
//    return oneDimensionalBoard;
}

GridSquare GameBoard::getSquare(int x, int y)
{
    GridSquare square = (m_gameBoard.at(x).at(y));
    return square;
}

void GameBoard::createRandomizedGameBoard(int height, int width)
{
    m_gameBoard = QVector<QVector<GridSquare *>>();
    for(int i = 0; i < height; i++) // Initialize starting with row by row
    {
        QVector<GridSquare *> currRow;
        for(int x = 0; x < width; x++) // Initialize starting with
        {
            GridSquare *newSquare = new GridSquare(this);
            newSquare.setSquareType(static_cast<GridSquare::BoardSquareType>(qrand() % 2));
            currRow.append(newSquare);
        }
        m_gameBoard.append(currRow);
    }
}
