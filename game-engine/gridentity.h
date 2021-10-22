#ifndef ENTITY_H
#define ENTITY_H

#include <QQuickItem>
#include <QVector>
#include "gridsquaredata.h"
#include "gridmatrix.h"

class GridEntity : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QPoint gridPos READ getGridPos WRITE setGridPos NOTIFY onGridPosChanged)
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

    void setPath(QVector<QPoint> path);

    Q_INVOKABLE void moveTo(QPoint target);

    Q_INVOKABLE bool pathHasSteps();
    Q_INVOKABLE void findPath(QPoint target);
    Q_INVOKABLE void followPath(int maxSteps = 1);
    void followPath(QVector<QPoint> &path, int maxSteps = 1);

signals:
    void onGridPosChanged(QPoint pos);
    void onGridMatrixChanged(GridMatrix *);

private:
    QPoint m_gridPos;

    QVector<QPoint> m_Path;

    GridMatrix *p_gridMatrix;
};

#endif // ENTITY_H
