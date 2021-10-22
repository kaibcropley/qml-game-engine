#ifndef MOVEMENTENUMS_H
#define MOVEMENTENUMS_H

#include <QObject>

class MovementEnums : public QObject
{
    Q_OBJECT
public:
    enum Directions {
        North = 0,
        NorthEast = 45,
        East = 90,
        SouthEast = 135,
        South = 180,
        SouthWest = 225,
        West = 270,
        NorthWest = 315
    };
    Q_ENUM(Directions)

    explicit MovementEnums(QObject *parent = 0);

signals:

public slots:
};

#endif // MOVEMENTENUMS_H
