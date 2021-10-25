#include "gridentityfactory.h"

GridEntityFactory::GridEntityFactory(QObject *parent) : QObject(parent)
{

}

 GridEntity GridEntityFactory::getGridEntity()
 {
     GridEntity newEntity;
     return newEntity;
 }
