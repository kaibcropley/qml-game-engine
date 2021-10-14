#ifndef ENTITY_H
#define ENTITY_H

#include <QQuickItem>
#include <QVector>
#include "gridsquaredata.h"

class GridEntity : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QPoint gridPos READ getGridPos WRITE setGridPos NOTIFY onGridPosChanged)
    Q_PROPERTY(int gridX READ getGridX WRITE setGridX NOTIFY onGridXChanged)
    Q_PROPERTY(int gridY READ getGridY WRITE setGridY NOTIFY onGridYChanged)
public:

    // Constructors
    explicit GridEntity(QQuickItem *parent = 0, int startX = 0, int startY = 0);
    GridEntity(const GridEntity &other);

    // Operators
    GridEntity operator=(const GridEntity&);

    // Grid Positioning getters and setters
    QPoint getGridPos();
    void setGridPos(QPoint pos);
    int getGridX();
    void setGridX(int newX);
    int getGridY();
    void setGridY(int newY);

    void setPath(QVector<QPoint> path);

    Q_INVOKABLE bool moveTo(QPoint target);
//    bool step(MovementDirections direction);

    Q_INVOKABLE void findPath(QPoint target);
    Q_INVOKABLE bool pathHasSteps();
    Q_INVOKABLE void followPath(int maxSteps = 1);
    void followPath(QVector<QPoint> &path, int maxSteps = 1);

signals:
    void onGridXChanged(int newX);
    void onGridYChanged(int newY);
    void onGridPosChanged(QPoint pos);

public slots:

private:
    QPoint m_gridPos;

    QVector<QPoint> m_Path;
};

#endif // ENTITY_H
