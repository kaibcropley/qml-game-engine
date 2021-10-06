#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <QObject>
#include <QPoint>

class CollisionManager : public QObject
{
    Q_OBJECT
public:
    explicit CollisionManager(QObject *parent = 0);

    Q_INVOKABLE bool rectanglesCollide(QPoint topLeftA, QPoint botRightA, QPoint topLeftB, QPoint botRightB);

signals:

public slots:
};

#endif // COLLISIONMANAGER_H
