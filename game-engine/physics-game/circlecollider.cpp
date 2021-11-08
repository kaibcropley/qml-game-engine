#include "circlecollider.h"

CircleCollider::CircleCollider()
{
    QObject::connect(this, &CircleCollider::widthChanged, this, &CircleCollider::updateRadius);
}

void CircleCollider::setRadius(int newRadius)
{
    if (m_radius != newRadius) {
        m_radius = newRadius;
        emit onRadiusChanged(m_radius);
    }
}

int CircleCollider::getRadius() const
{
    return m_radius;
}

void CircleCollider::updateRadius()
{
    if (width() > 0) {
        setRadius(width() / 2);
    } else {
        setRadius(0);
    }
}
