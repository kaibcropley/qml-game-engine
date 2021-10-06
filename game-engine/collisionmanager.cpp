#include "collisionmanager.h"
#include <QDebug>
#include <QVariantMap>

CollisionManager::CollisionManager(QObject *parent) : QObject(parent)
{

}

bool CollisionManager::rectanglesCollide(QPoint topLeftA, QPoint botRightA, QPoint topLeftB, QPoint botRightB)
{
    return (topLeftA.x() < botRightB.x() &&
             topLeftB.x() < botRightA.x() &&
             topLeftA.y() < botRightB.y() &&
             topLeftB.y() < botRightA.y());
}
