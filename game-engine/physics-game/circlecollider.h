#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

#include <QObject>
#include "collider.h"

class CircleCollider : public Collider
{
    Q_OBJECT
    Q_PROPERTY(int radius READ getRadius WRITE setRadius NOTIFY onRadiusChanged)
public:
    explicit CircleCollider();

    void setRadius(int newRadius);
    int getRadius() const;

signals:
    void onRadiusChanged(int radius);

public slots:
    void updateRadius();

private:
    int m_radius;
};

#endif // CIRCLECOLLIDER_H
