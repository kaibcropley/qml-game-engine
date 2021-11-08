#include "rectanglecollider.h"

RectangleCollider::RectangleCollider()
{

}



QPoint RectangleCollider::getTopLeftCoordinates() const
{
    QPoint p(position().toPoint());
    return p;
}

QPoint RectangleCollider::getBotRightCoordinates() const
{
    return (QPoint(x() + width(), y() + height()));
}
