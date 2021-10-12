#ifndef ENTITY_H
#define ENTITY_H

#include <QQuickItem>
#include <QVector>
#include "gridsquaredata.h"

class GridEntity : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int gridX READ getGridX WRITE setGridX NOTIFY onGridXChanged)
    Q_PROPERTY(int gridY READ getGridY WRITE setGridY NOTIFY onGridYChanged)
public:
    enum MovementDirections {
        GRID_W,
        GRID_E,
        GRID_N,
        GRID_S,
        GRID_NE,
        GRID_NW,
        GRID_SE,
        GRID_SW

    };
    Q_ENUM(MovementDirections)


    // Constructors
    explicit GridEntity(QQuickItem *parent = 0, int startX = 0, int startY = 0);
    GridEntity(const GridEntity &other);

    // Operators
    GridEntity operator=(const GridEntity&);

    // Grid X and Y getter and setters
    void setGridX(int newX);
    int getGridX();
    void setGridY(int newY);
    int getGridY();

    Q_INVOKABLE bool moveTo(int newX, int newY);
    bool step(MovementDirections direction);

    Q_INVOKABLE void findPath(QVector<QVector<GridSquareData *>> gameBoard, int targetX, int targetY);
    bool findNextPathStep(QVector<QVector<GridSquareData *>> *gameBoard, int currX, int currY, int targetX, int targetY);

    Q_INVOKABLE bool pathHasSteps();
    Q_INVOKABLE void followPath(int maxSteps);
    void followPath(int maxSteps, QVector<MovementDirections> &path);

    bool canMoveTo(QVector<QVector<GridSquareData *>> *gameBoard, int x, int y);
    bool canMoveTo(GridSquareData * square);


//    void solveMaze(GameBoard gameBoard, int targetX, int targetY);
//    void mazeHelper(GameBoard *gameboard, int targetX, int targetY);

signals:
    void onGridXChanged(int newX);
    void onGridYChanged(int newY);

public slots:

private:
    int m_gridX;
    int m_gridY;

    QVector<MovementDirections> m_path;
};

#endif // ENTITY_H
