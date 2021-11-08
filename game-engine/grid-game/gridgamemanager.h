#ifndef GRIDGAMEMANAGER_H
#define GRIDGAMEMANAGER_H

#include <QQuickItem>
#include "entitymanager.h"
#include "gridmatrix.h"


class GridGameManager : public QQuickItem
{
    Q_OBJECT
public:
    GridGameManager();

    Q_INVOKABLE void initializeGridGame(int rows, int columns);

signals:

public slots:

private:
    GridMatrix *m_gridMatrix;
    EntityManager *m_entityManager;
};

#endif // GRIDGAMEMANAGER_H
