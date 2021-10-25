#ifndef GRIDENTITYFACTORY_H
#define GRIDENTITYFACTORY_H

#include <QObject>
#include "gridentity.h"

class GridEntityFactory : public QObject
{
    Q_OBJECT
public:
    explicit GridEntityFactory(QObject *parent = 0);

    Q_INVOKABLE GridEntity getGridEntity();

signals:

public slots:
};

#endif // GRIDENTITYFACTORY_H
