#ifndef RECTANGLECOLLIDER_H
#define RECTANGLECOLLIDER_H

#include <QQuickItem>
#include "collider.h"

class RectangleCollider : public Collider
{
    Q_OBJECT
public:
    RectangleCollider();

    QPoint getTopLeftCoordinates() const;
    QPoint getBotRightCoordinates() const;
signals:

public slots:

private:

};

#endif // RECTANGLECOLLIDER_H
