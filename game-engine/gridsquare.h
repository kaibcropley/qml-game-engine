#ifndef GRIDSQUARE_H
#define GRIDSQUARE_H

#include <QObject>

class GridSquare : public QObject
{
    Q_OBJECT
    Q_PROPERTY(BoardSquareType boardSquareType READ getSquareType WRITE setSquareType NOTIFY onSquareTypeChanged)
public:
    enum BoardSquareType {
        DIRT,
        GRASS
    };
    Q_ENUM(BoardSquareType)

    explicit GridSquare(QObject *parent = 0);
    explicit GridSquare(const GridSquare &other);
//    GridSquare(QObject *parent = 0, BoardSquareType boardSquareType = BoardSquareType::DIRT);

    GridSquare operator=(const GridSquare&);

    Q_INVOKABLE void setSquareType(BoardSquareType boardSquareType);
    Q_INVOKABLE BoardSquareType getSquareType() const;

signals:
    void onSquareTypeChanged(BoardSquareType boardSquareType);

public slots:

private:
    BoardSquareType m_squareType;
    bool m_containsFood;
};

#endif // GRIDSQUARE_H
