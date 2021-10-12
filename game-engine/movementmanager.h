#ifndef MOVEMENTMANAGER_H
#define MOVEMENTMANAGER_H

#include <QObject>

class MovementManager : public QObject
{
    Q_OBJECT
public:
    explicit MovementManager(QObject *parent = 0);

    void getPath(QObject target, int fromX, int fromY, int toX, int toY);

signals:

public slots:
};

#endif // MOVEMENTMANAGER_H
