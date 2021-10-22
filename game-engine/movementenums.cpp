#include "movementenums.h"
#include "qdebug.h"

MovementEnums::MovementEnums(QObject *parent) : QObject(parent)
{

}

MovementEnums::Directions MovementEnums::getDirection(QPoint source, QPoint target)
{
    if (source.y() < target.y()) {
        if (source.x() < target.x()) {
            return SouthEast;
        } else if (source.x() > target.x()) {
            return SouthWest;
        } else {
            return South;
        }
    } else if ((source.y() > target.y())) {
        if (source.x() < target.x()) {
            return NorthEast;
        } else if (source.x() > target.x()) {
            return NorthWest;
        } else {
            return North;
        }
    } else {
        if (source.x() < target.x()) {
            return East;
        } else if (source.x() > target.x()) {
            return West;
        } else {
            return North;
        }
    }
}
