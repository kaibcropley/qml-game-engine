#ifndef PATHFINDER_H
#define PATHFINDER_H

//#include <QObject>
#include <QPoint>
#include "gridmatrix.h"
#include "movementenums.h"

class PathFinder // : public QObject
{
//    Q_OBJECT
private:
    static PathFinder* m_instance;
    PathFinder();

    // TODO find better place to put Node constructors -- Look into moving to .cpp file
    struct Node {
        Node *parent;
        QPoint loc;
        int g = 1;
        int h;
        int f;

        Node()
        {
            qDebug() << "SOMEONE IS INCORRECTLY GENERATING NODES";
        }

        Node(QPoint current, int manhattanDistance)
        {
            parent = nullptr;
            // Distance estimation: Manhattan Distance - https://xlinux.nist.gov/dads/HTML/manhattanDistance.html
            // G = the movement cost to move from the starting point A to a given square on the grid
            g = 1; //For now use 1 //qFabs(source.x() - current.x()) + qFabs(source.y() - current.y());
            // H = the estimated movement cost to move from that given square on the grid to the final destination
            h = manhattanDistance;

            f = g + h;
            loc = current;
        }

        Node(Node &par, QPoint current, int manhattanDistance)
        {
            parent = &par;

            // G = the movement cost to move from the starting point A to a given square on the grid
            if (parent != nullptr) {
                g = parent->g + 1;
            } else {
                g = 1;
            }

            // H = the estimated movement cost to move from that given square on the grid to the final destination
            h = manhattanDistance;

            f = g + h;
            loc = current;
        }

        bool operator ==(const Node &other) const
        {
            return loc == other.loc; // && g == other.g && h == other.h && f == other.f;
        }

        bool operator ==(const QPoint &other) const
        {
            return loc == other; // && g == other.g && h == other.h && f == other.f;
        }
    };
        /* Here will be the instance stored. */

        /* Private constructor to prevent instancing. */
public:
    static PathFinder *getInstance();

    QVector<QPoint> findPath(GridMatrix *gameBoard, QPoint source, QPoint target);
    QVector<QPoint> dijkstra(GridMatrix *gameBoard, QPoint source, QPoint target);

    // Path finding helpers
    bool isMoveValid(GridMatrix *gameBoard, QPoint point);
    int calculateManhattanDistance(QPoint p1, QPoint p2);
    QPoint movePointDirection(MovementEnums::Directions direction, QPoint point, int changeLength = 1);

    // By using this we significantly increase search times by not having to initialize a node to check if the vector contains it
    bool nodeVectorContainsPoint(QVector<Node *> vec, QPoint point);


signals:

public slots:
};

#endif // PATHFINDER_H
