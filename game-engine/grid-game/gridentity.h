#ifndef ENTITY_H
#define ENTITY_H

#include <QQuickItem>
#include <QVector>
#include "grid-game/gridmatrix.h"
#include "grid-game/movementenums.h"

class GridEntity : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QPoint gridPos READ getGridPos WRITE setGridPos NOTIFY onGridPosChanged)
    Q_PROPERTY(bool movementEnabled READ getMovementEnabled WRITE setMovementEnabled NOTIFY onMovementEnabledChanged)
    Q_PROPERTY(MovementEnums::Directions lastDirection READ getLastDirection WRITE setLastDirection NOTIFY onLastDirectionChanged)
public:

    // Constructors
    explicit GridEntity(QQuickItem *parent = 0);
    GridEntity(const GridEntity &other);

    // Operators
    GridEntity operator=(const GridEntity&);

    QPoint getGridPos();
    void setGridPos(QPoint pos);

    GridMatrix * getGridMatrix();
    void setGridMatrix(GridMatrix *newGridMatrix);

    // Essencially disables setGridPos
    bool getMovementEnabled();
    void setMovementEnabled(bool enable);

    // Allows UI to know which direction to rotate in
    MovementEnums::Directions getLastDirection();
    void setLastDirection(MovementEnums::Directions newDirection);

    // Essencially a Q_INVOKABLE setGridPos w/ a more readable name b/c they can use Q_PROPERTY gridPos to moveTo
    Q_INVOKABLE void moveTo(QPoint target);

    void setPath(QVector<QPoint> path);
    Q_INVOKABLE QPoint getPathStep(int pathStepIndex);
    Q_INVOKABLE QPoint getPathNextStep();
    Q_INVOKABLE QPoint getPathTarget();

    Q_INVOKABLE int pathLength();
    Q_INVOKABLE bool pathHasSteps();
        // Finds and sets a path (m_path) on the current matrix (p_gridMatrix)
    Q_INVOKABLE bool findPath(QPoint target);
    Q_INVOKABLE bool followPath(int maxSteps = 1);
    bool followPath(QVector<QPoint> &path, int maxSteps = 1);

signals:
    void onGridMatrixChanged(GridMatrix *);

    void onMovementEnabledChanged(bool enabled);
    // onGridPosChanged won't ever signal if movementEnabled/m_movementEnabled = false
    void onGridPosChanged(QPoint pos);

    // Used by UI to rotate the sprite
    void onLastDirectionChanged(MovementEnums::Directions direction);

private:
    GridMatrix *p_gridMatrix;
    QPoint m_gridPos;

    bool m_movementEnabled;
    QVector<QPoint> m_path;
    MovementEnums::Directions m_lastDirection;
};

#endif // ENTITY_H
