#ifndef GRIDSQUARE_H
#define GRIDSQUARE_H

#include <QQuickItem>
#include <QVariantMap>

class GridSquareData : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(BoardSquareType boardSquareType READ getSquareType WRITE setSquareType NOTIFY onSquareTypeChanged)
    Q_PROPERTY(bool blocked READ getBlocked WRITE setBlocked NOTIFY onBlockedChanged)
    Q_PROPERTY(bool containsFood READ getContainsFood WRITE setContainsFood NOTIFY onContainsFoodChanged)
public:
    enum BoardSquareType {
        DIRT,
        GRASS
    };
    Q_ENUM(BoardSquareType)

    explicit GridSquareData(QQuickItem *parent = 0);
    GridSquareData(const GridSquareData &other);
//    GridSquare(QObject *parent = 0, BoardSquareType boardSquareType = BoardSquareType::DIRT);

    GridSquareData operator=(const GridSquareData&);

    QVariantMap toQVariantMap();

    void setSquareType(BoardSquareType boardSquareType);
    BoardSquareType getSquareType() const;

    void setBlocked(bool blocked);
    bool getBlocked() const;

    void setContainsFood(bool containsFood);
    bool getContainsFood() const;

    void setVisited(bool visited);
    bool getVisited();
signals:
    void onSquareTypeChanged(BoardSquareType boardSquareType);
    void onBlockedChanged(bool blocked);
    void onContainsFoodChanged(bool containsFood);

public slots:

private:
    BoardSquareType m_squareType;
    bool m_blocked;
    bool m_containsFood;

    // m_visited is used for path finding to ensure entities aren't double checking spaces
    //  Could be optimized better than having this around for each instance but that can be done later
    bool m_visited;
};

#endif // GRIDSQUARE_H
