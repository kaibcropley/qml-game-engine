#include "collider.h"

Collider::Collider()
{

}

Collider::Collider(const Collider &other)
{
//    this = other;
}

QPoint Collider::getCenterCoordinates() const
{
    QPoint center(position().toPoint());

    if (width() > 0) { // So no 0/2 situation
        center.setX(x() + (width() / 2));
    }

    if (height() > 0) { // So no 0/2 situation
        center.setY(y() + (height() / 2));
    }

    return center;
}


//void Collider::applyForce(QVector2D force)
//{
////    float forceMagnitude;
////    m_deltaTime = deltaTime;
//    m_forceApplied = force;

////    forceMagnitude = force.length();
////    m_acceleration = forceMagnitude / m_mass;
//}

//void Collider::resetForce()
//{
//    applyForce(QVector2D(0,0));
//}

//void Collider::calculateVelocity()
//{
//    m_velocity += ((1 / m_mass) * m_forceApplied) * m_deltaTime;
////    qDebug() << "Collider::calculateVelocity()" << m_velocity;
//}

//void Collider::resetVelocity()
//{
//    m_velocity = QVector2D(0,0);
//}

//void Collider::updatePosition()
//{
////    qDebug() << "Update position";
////    qDebug() << m_velocity * m_deltaTime << (m_velocity * m_deltaTime).toPointF();
//    setPosition(position() + (m_velocity * m_deltaTime).toPointF());
//}

////float dotProduct(QVector2D)
////{
////    return rv
////}

//void Collider::resolveCollision(Collider *other)
//{
////    qDebug() << "Collider::resolveCollision";
//    // Calculate relative velocity
//    QVector2D rv = other->m_velocity - m_velocity;

//    // Calculate relative velocity in terms of the normal direction
////    float velAlongNormal = dotProduct( rv, rv.normalized() );
////    float velAlongNormal = (rv + rv.normalized());
//    float velAlongNormal = QVector2D::dotProduct(rv, rv.normalized());

//    // Do not resolve if velocities are separating
//    if (velAlongNormal > 0) {
//        qDebug() << "Collider::resolveCollision Separating" << velAlongNormal;
//        return;
//    }

//    // Calculate restitution
//    float e = std::min( m_restitution, other->m_restitution);

//    // Calculate impulse scalar
//    float j = -(1 + e) * velAlongNormal;
//    j /= (1 / m_mass) + (1 / other->m_mass);

//    // Apply impulse
//    QVector2D impulse = j * rv.normalized();
//    m_velocity -= (1 / m_mass) * impulse;
//    other->m_velocity += (1 / other->m_mass) * impulse;

//    qDebug() << "Collider::resolveCollision m_velocity" << m_velocity << other->m_velocity;
//    return;
//}
