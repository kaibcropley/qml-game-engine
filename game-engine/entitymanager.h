#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <QObject>
#include "gridentity.h"
#include "gridmatrix.h"

class EntityManager : public QObject
{
    Q_OBJECT
public:
    explicit EntityManager(QObject *parent = 0, GridMatrix *incomingGridMatrix = nullptr);

    Q_INVOKABLE bool registerEntity(GridEntity *entity);

    Q_INVOKABLE bool findPath(QPoint target); // Defaults
    Q_INVOKABLE bool findPath(QPoint source, QPoint target);
    Q_INVOKABLE void updateEntities();

signals:

public slots:

private:
    // TODO turn into list of targets -- Useful if qquick item https://doc.qt.io/archives/qt-5.6/qqmllistproperty.html
    GridEntity *targetEntity;

    GridMatrix *gridMatrix;
};

#endif // ENTITYMANAGER_H
