#ifndef ENTITY_H
#define ENTITY_H

#include <QQuickItem>
#include <QVector>
#include "grid-game/gridsquaredata.h"
#include "grid-game/gridmatrix.h"
#include "grid-game/movementenums.h"

class GridEntity : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QPoint gridPos READ getGridPos WRITE setGridPos NOTIFY onGridPosChanged)
    Q_PROPERTY(MovementEnums::Directions lastDirection READ getLastDirection WRITE setLastDirection NOTIFY onLastDirectionChanged)
    Q_PROPERTY(bool movementEnabled READ getMovementEnabled WRITE setMovementEnabled NOTIFY onMovementEnabledChanged)
public:

    // Constructors
    explicit GridEntity(QQuickItem *parent = 0);
    GridEntity(const GridEntity &other);

    // Operators
    GridEntity operator=(const GridEntity&);

    // Grid Positioning getters and setters
    QPoint getGridPos();
    void setGridPos(QPoint pos);

    GridMatrix * getGridMatrix();
    void setGridMatrix(GridMatrix *newGridMatrix);

    bool getMovementEnabled();
    void setMovementEnabled(bool enable);

    // Allows UI to know which direction to rotate in
    MovementEnums::Directions getLastDirection();
    void setLastDirection(MovementEnums::Directions newDirection);

    void setPath(QVector<QPoint> path);

    Q_INVOKABLE void moveTo(QPoint target);

    Q_INVOKABLE bool pathHasSteps();
    Q_INVOKABLE void findPath(QPoint target);
    Q_INVOKABLE void followPath(int maxSteps = 1);
    void followPath(QVector<QPoint> &path, int maxSteps = 1);

signals:
    void onGridPosChanged(QPoint pos);
    void onGridMatrixChanged(GridMatrix *);

    void onLastDirectionChanged(MovementEnums::Directions direction);

    void onMovementEnabledChanged(bool enabled);

private:
    QPoint m_gridPos;

    QVector<QPoint> m_Path;

    GridMatrix *p_gridMatrix;

    bool m_movementEnabled;

    MovementEnums::Directions m_lastDirection;
};

#endif // ENTITY_H
