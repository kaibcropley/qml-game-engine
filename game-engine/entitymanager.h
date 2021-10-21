#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <QObject>
#include "gridentity.h"
#include "gameboard.h"

class EntityManager : public QObject
{
    Q_OBJECT
public:
    explicit EntityManager(QObject *parent = 0, GameBoard *incomingGameBoard = nullptr);

    Q_INVOKABLE void registerEntity(GridEntity *entity);

    Q_INVOKABLE void findPath(int targetX, int targetY);
    Q_INVOKABLE void updateEntities();

signals:

public slots:

private:
    // TODO turn into list of targets -- Useful if qquick item https://doc.qt.io/archives/qt-5.6/qqmllistproperty.html
    QVector<GridEntity *> m_entities;

    GameBoard *gameBoard;


};

#endif // ENTITYMANAGER_H
