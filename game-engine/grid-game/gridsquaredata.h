#ifndef GRIDSQUARE_H
#define GRIDSQUARE_H

#include <QQuickItem>
#include <QVariantMap>

class GridSquareData : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString boardSquareType READ getSquareType WRITE setSquareType NOTIFY onSquareTypeChanged)
    Q_PROPERTY(bool movementAllowed READ getMovementAllowed WRITE setMovementAllowed NOTIFY onBlockedChanged)
    Q_PROPERTY(bool containsFood READ getContainsFood WRITE setContainsFood NOTIFY onContainsFoodChanged)

    Q_PROPERTY(QPoint gridPos READ getGridPos WRITE setGridPos NOTIFY onGridPosChanged)
    Q_PROPERTY(int gridX READ getGridX NOTIFY onGridXChanged)
    Q_PROPERTY(int gridY READ getGridY NOTIFY onGridYChanged)
public:

    explicit GridSquareData(QQuickItem *parent = 0, QPoint gridPos = QPoint(0,0));
    GridSquareData(const GridSquareData &other);
//    GridSquare(QObject *parent = 0, BoardSquareType boardSquareType = BoardSquareType::DIRT);

    GridSquareData operator=(const GridSquareData&);

    QVariantMap toQVariantMap();

    void setSquareType(QString boardSquareType);
    QString getSquareType() const;

    void setMovementAllowed(bool blocked);
    bool getMovementAllowed() const;

    void setContainsFood(bool containsFood);
    bool getContainsFood() const;

    void setVisited(bool visited);
    bool getVisited();

    // Grid Positioning getters and setters
    QPoint getGridPos();
    void setGridPos(QPoint pos);
    int getGridX();
    void setGridX(int newX);
    int getGridY();
    void setGridY(int newY);

signals:
    void onSquareTypeChanged(QString boardSquareType);
    void onBlockedChanged(bool blocked);
    void onContainsFoodChanged(bool containsFood);

    void onGridXChanged(int newX);
    void onGridYChanged(int newY);
    void onGridPosChanged(QPoint pos);

public slots:

private:
    QString m_squareType;
    bool m_movementAllowed;
    bool m_containsFood;

    QPoint m_gridPos;

    // m_visited is used for path finding to ensure entities aren't double checking spaces
    //  Could be optimized better than having this around for each instance but that can be done later
    bool m_visited;
};

#endif // GRIDSQUARE_H
