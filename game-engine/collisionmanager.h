#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <QObject>
#include <QPoint>
#include <QRect>

class CollisionManager : public QObject
{
    Q_OBJECT
public:
    explicit CollisionManager(QObject *parent = 0);

    Q_INVOKABLE bool rectanglesCollide(QRect rectA, QRect rectB);
    Q_INVOKABLE bool rectanglesCollide(QPoint topLeftA, QPoint botRightA, QPoint topLeftB, QPoint botRightB);

    Q_INVOKABLE bool circlesCollide(QPoint cirACenter, int aRadius, QPoint cirBCenter, int bRadius);
    Q_INVOKABLE int distanceBetweenCircles(QPoint aCenter, QPoint bPoint);

    Q_INVOKABLE bool circleAndRectangleCollide(QPoint cirCenter, int cirRadius, QPoint rectCenter, int rectWidth, int rectHeight);

signals:

public slots:
};

#endif // COLLISIONMANAGER_H
