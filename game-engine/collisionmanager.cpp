#include "collisionmanager.h"
#include <QDebug>
#include <QVariantMap>
#include <QtMath>

CollisionManager::CollisionManager(QObject *parent) : QObject(parent)
{

}

bool CollisionManager::rectanglesCollide(QRect rectA, QRect rectB)
{
    qDebug() << rectA;
    qDebug() << rectA.intersects(rectB);
    return false;
}

bool CollisionManager::rectanglesCollide(QPoint topLeftA, QPoint botRightA, QPoint topLeftB, QPoint botRightB)
{
    return (topLeftA.x() < botRightB.x() &&
             topLeftB.x() < botRightA.x() &&
             topLeftA.y() < botRightB.y() &&
             topLeftB.y() < botRightA.y());
}

// From https://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection
// User e.James - https://stackoverflow.com/users/33686/e-james
bool CollisionManager::circleAndRectangleCollide(QPoint cirCenter, int cirRadius, QPoint rectCenter, int rectWidth, int rectHeight)
{
    int circleDistanceX = qFabs(cirCenter.x() - rectCenter.x());
    int circleDistanceY = qFabs(cirCenter.y() - rectCenter.y());

    int halfRectWidth = rectWidth / 2;
    int halfRectHeight = rectHeight / 2;

    if (circleDistanceX > (halfRectWidth + cirRadius) || circleDistanceY > (halfRectHeight + cirRadius))
    {
        return false;
    }

    if (circleDistanceX <= (halfRectWidth) || circleDistanceY <= (halfRectHeight))
    {
        return true;
    }

    return ((circleDistanceX - halfRectWidth) ^ 2 + (circleDistanceY - halfRectHeight) ^ 2 <= (cirRadius ^ 2));
}

bool CollisionManager::circlesCollide(QPoint cirACenter, int aRadius, QPoint cirBCenter, int bRadius) {
    return distanceBetweenCircles(cirACenter, cirBCenter) < aRadius + bRadius;
}

int CollisionManager::distanceBetweenCircles(QPoint aCenter, QPoint bPoint) {
    int dx = aCenter.x() - bPoint.x();
    int dy = aCenter.y() - bPoint.y();
    return qSqrt(dx * dx + dy * dy);
}
