#ifndef MOVEMENTENUMS_H
#define MOVEMENTENUMS_H

// Requires that qmlRegisterType<MovementEnums>("Movement.Enums", 1, 0, "MovementEnums");

#include <QObject>

class MovementEnums : public QObject
{
    Q_OBJECT
public:
    enum Directions
    {
        N = 0,
        NE = 45,
        E = 90,
        SE = 135,
        S = 180,
        SW = 225,
        W = 270,
        NW = 315
    };
    Q_ENUMS(Directions)

    explicit MovementEnums(QObject *parent = 0);
};

#endif // MOVEMENTENUMS_H
