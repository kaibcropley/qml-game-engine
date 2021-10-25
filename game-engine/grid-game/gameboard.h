#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QObject>
#include <QVariant>
#include <QVector>
#include "gridsquaredata.h"

class GameBoard : public QObject
{
    Q_OBJECT
public:
    explicit GameBoard(QObject *parent = 0);

    // Cannot be Q_INVOKABLE due QVector<QVector<int>> not being a valid type
    //  See here for info https://doc.qt.io/qt-5/qtqml-cppintegration-data.html
    void setGameBoard(QVector<QVector<GridSquareData *>> newBoard);
    QVector<QVector<GridSquareData *>> getGameBoard();

    Q_INVOKABLE void getType(QObject *ptr);

    // Returns a QVariantMap/JSON obj with data for the UI
    Q_INVOKABLE QVariantMap getSquareMap(int x, int y);
    GridSquareData* at(int x, int y);
    GridSquareData* getSquare(int x, int y);
    // Returns an array of QVariantMap/JSON objects as one long array for the grid repeater
    Q_INVOKABLE QVariant gameBoardToOneDimension();

    Q_INVOKABLE void createRandomizedGameBoard(int height, int width);

    void getPath(int fromX, int fromY, int toX, int toY);

signals:

public slots:

private:
    int getRandomInt(); // TODO get out of here into a lib class

    QVector<QVector<GridSquareData *>> m_gameBoard;
};

#endif // GAMEBOARD_H
