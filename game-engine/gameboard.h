#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QObject>
#include <QVector>
#include "gridsquare.h"

class GameBoard : public QObject
{
    Q_OBJECT
public:
    explicit GameBoard(QObject *parent = 0);

    // Cannot be Q_INVOKABLE due QVector<QVector<int>> not being a valid type
    //  See here for info https://doc.qt.io/qt-5/qtqml-cppintegration-data.html
    void setGameBoard(QVector<QVector<GridSquare *>> newBoard);
    QVector<QVector<GridSquare *>> gameBoard();

    Q_INVOKABLE GridSquare * gameBoardToOneDimension();
    Q_INVOKABLE GridSquare getSquare(int x, int y);


    Q_INVOKABLE void createRandomizedGameBoard(int height, int width);

signals:

public slots:

private:
    QVector<QVector<GridSquare *>> m_gameBoard;
};

#endif // GAMEBOARD_H
