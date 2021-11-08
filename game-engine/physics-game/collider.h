#ifndef COLLIDER_H
#define COLLIDER_H

#include <QQuickItem>

class Collider : public QQuickItem
{
    Q_OBJECT
public:
    Collider();
    Collider(const Collider&);

    QPoint getCenterCoordinates() const;

//    Q_INVOKABLE void applyForce(QVector2D force);
//    Q_INVOKABLE void resetForce();

//    Q_INVOKABLE void calculateVelocity();
//    Q_INVOKABLE void resetVelocity();

//    Q_INVOKABLE void updatePosition();

//    Q_INVOKABLE void resolveCollision(Collider *other);

signals:

public slots:

private:
//    float m_mass;
//    float m_inverseMass;
//    float m_restitution; // 0 < m_restitution < 1
//    QVector2D m_velocity;

//    QVector2D m_forceApplied;
//    int m_deltaTime = 1;
};

#endif // COLLIDER_H
