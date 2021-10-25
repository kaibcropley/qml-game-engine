#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <QObject>
//#include <QQmlListProperty>
#include "gridentity.h"
#include "gridmatrix.h"

class EntityManager : public QObject
{
    Q_OBJECT
public:
    explicit EntityManager(QObject *parent = 0, GridMatrix *incomingGridMatrix = nullptr);

    Q_INVOKABLE bool registerEntity(GridEntity *entity);
    Q_INVOKABLE void updateEntities();

signals:

public slots:

private:
    // TODO turn into list of targets -- Useful if qquick item https://doc.qt.io/archives/qt-5.6/qqmllistproperty.html
    QVector<GridEntity *> entities;

    GridMatrix *m_gridMatrix;
};

#endif // ENTITYMANAGER_H
