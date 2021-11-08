#include "collisionmanager.h"
#include <QDebug>
#include <QVariantMap>
#include <QtMath>

CollisionManager::CollisionManager(QObject *parent) : QObject(parent)
{

}

bool CollisionManager::collision(QQuickItem *a, QQuickItem *b)
{
//    qDebug() << "CollisionManager::collision" << a->width();
    const CircleCollider *cir = qobject_cast<const CircleCollider *>(a);
    if (cir != NULL) {
        const CircleCollider *cir2 = qobject_cast<const CircleCollider *>(b);
        if (cir2 != NULL) {
//            qDebug() << "Testing circles";
            return circlesCollide(cir, cir2);
        }

        const RectangleCollider *rect2 = qobject_cast<const RectangleCollider *>(b);
        if (rect2 != NULL) {
            return circleAndRectangleCollide(cir, rect2);
        }
        return false;
    }

    const RectangleCollider *rect = qobject_cast<const RectangleCollider *>(a);
    if (rect != NULL) {
        const CircleCollider *cir2 = qobject_cast<const CircleCollider *>(b);
        if (cir2 != NULL) {
            return circleAndRectangleCollide(cir2, rect);
        }

        const RectangleCollider *rect2 = qobject_cast<const RectangleCollider *>(b);
        if (rect2 != NULL) {
            return rectanglesCollide(rect, rect2);
        }
        return false;
    }

    return false;
}

bool CollisionManager::rectanglesCollide(const RectangleCollider *a, const RectangleCollider *b)
{
    return rectanglesCollide(a->getTopLeftCoordinates(), a->getBotRightCoordinates(), b->getTopLeftCoordinates(), b->getBotRightCoordinates());
}

bool CollisionManager::rectanglesCollide(const QPoint topLeftA, const QPoint botRightA, const QPoint topLeftB, const QPoint botRightB)
{
    return (topLeftA.x() < botRightB.x() &&
             topLeftB.x() < botRightA.x() &&
             topLeftA.y() < botRightB.y() &&
             topLeftB.y() < botRightA.y());
}

bool CollisionManager::circlesCollide(const CircleCollider *a, const CircleCollider *b)
{
    return circlesCollide(a->getCenterCoordinates(), a->getRadius(), b->getCenterCoordinates(), b->getRadius());
}

bool CollisionManager::circlesCollide(const QPoint cirACenter, int aRadius, const QPoint cirBCenter, int bRadius)
{
    return distanceBetweenCircles(cirACenter, cirBCenter) < aRadius + bRadius;
}

int CollisionManager::distanceBetweenCircles(const QPoint aCenter, const QPoint bPoint)
{
    int dx = aCenter.x() - bPoint.x();
    int dy = aCenter.y() - bPoint.y();
    return qSqrt(dx * dx + dy * dy);
}

bool CollisionManager::circleAndRectangleCollide(const CircleCollider *cir, const RectangleCollider *rect)
{
    return circleAndRectangleCollide(cir->getCenterCoordinates(), cir->getRadius(), rect->getCenterCoordinates(), rect->width(), rect->height());
}

// From https://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection
// User e.James - https://stackoverflow.com/users/33686/e-james
bool CollisionManager::circleAndRectangleCollide(const QPoint cirCenter, int cirRadius, const QPoint rectCenter, int rectWidth, int rectHeight)
{
    int circleDistanceX = qFabs(cirCenter.x() - rectCenter.x());
    int circleDistanceY = qFabs(cirCenter.y() - rectCenter.y());

    int halfRectWidth = rectWidth;//rectWidth / 2;
    int halfRectHeight = rectHeight;//rectHeight / 2;

    if (circleDistanceX > (halfRectWidth + cirRadius) || circleDistanceY > (halfRectHeight + cirRadius))
    {
        return false;
    }

    if (circleDistanceX <= (halfRectWidth) || circleDistanceY <= (halfRectHeight))
    {
        return true;
    }

    return (((circleDistanceX - halfRectWidth) ^ 2) + ((circleDistanceY - halfRectHeight) ^ 2) <= (cirRadius ^ 2));
}


