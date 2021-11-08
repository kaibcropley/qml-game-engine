#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <QObject>
#include <QPoint>
//#include "collider.h"
#include "rectanglecollider.h"
#include "circlecollider.h"

class CollisionManager : public QObject
{
    Q_OBJECT
public:
    explicit CollisionManager(QObject *parent = 0);

    Q_INVOKABLE bool collision(QQuickItem *a, QQuickItem *b);

    Q_INVOKABLE bool rectanglesCollide(const RectangleCollider *a, const RectangleCollider *b);
    Q_INVOKABLE bool rectanglesCollide(const QPoint topLeftA, const QPoint botRightA, const QPoint topLeftB, const QPoint botRightB);

    Q_INVOKABLE bool circlesCollide(const CircleCollider *a, const CircleCollider *b);
    bool circlesCollide(const QPoint cirACenter, int aRadius, const QPoint cirBCenter, int bRadius);
    Q_INVOKABLE int distanceBetweenCircles(const QPoint aCenter, const QPoint bPoint);

    Q_INVOKABLE bool circleAndRectangleCollide(const CircleCollider *cir, const RectangleCollider *rect);
    Q_INVOKABLE bool circleAndRectangleCollide(const QPoint cirCenter, int cirRadius, const QPoint rectCenter, int rectWidth, int rectHeight);

signals:

public slots:
};

#endif // COLLISIONMANAGER_H
