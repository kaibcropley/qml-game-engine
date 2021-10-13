#include "pathfinder.h"
#include <QtMath>

// Set singleton instance to 0
PathFinder* PathFinder::m_instance = 0;

PathFinder::PathFinder()
{

}

PathFinder* PathFinder::getInstance()
{
    if (m_instance == 0) {
        m_instance = new PathFinder;
    }
    return m_instance;
}

void PathFinder::findPath(GridMatrix *gridMatrix, QPoint source, QPoint target)
{
    if (gridMatrix->rows() < 1 || gridMatrix->columns() < 1) {
        qDebug() << "PathFinder::findPath: Invalid grid matrix";
        return;
    }

    if (source == target) {
        qDebug() << "PathFinder::findPath: QPoint source == QPoint target";
        return;
    }

    qDebug() << "findPath( matrix," << source << "," << target << ")";
    dijkstra(gridMatrix, source, target);
}

// Dijkstra's algorithm for pathfinding
//  https://wiki.jmonkeyengine.org/docs/3.3/contributions/_attachments/Astar.pdf
//  Current implementation notes
//      This currently will fail to update a grid's parent if we find a faster way to that square, this isn't a big concern with movement being limited to 1 square tho
bool PathFinder::dijkstra(GridMatrix *gridMatrix, QPoint source, QPoint target)
{
    // Start node can be found by parent == nullptr
    Node *startNode = new Node(source, calculateManhattanDistance(source, target));

    QVector<Node *> untestedNodes; // open list
    QVector<Node *> testedNodes; // closed list
    untestedNodes.append(startNode);

    Node *currentNode = startNode;

    while (untestedNodes.size() > 0)
    {
        if (currentNode->loc == target) {
            qDebug() << "Success!!!";
            qDebug() << "Winning spot:" << currentNode->loc << currentNode->parent->loc;
            return true;
        }

        Node *lowest = untestedNodes.at(0);
        int lowestIndex = 0;
        for (int i = 0; i < untestedNodes.size(); i++) {
            if (lowest->f > untestedNodes.at(i)->f) {
                lowest = untestedNodes.at(i);
                lowestIndex = i;
            }
        }
        currentNode = lowest;
        testedNodes.append(lowest);
        untestedNodes.remove(lowestIndex);

        QPoint north = movePointDirection(MovementDirections::GRID_N, currentNode->loc);
        if (isMoveValid(gridMatrix, north)) {
            if (!nodeVectorContainsPoint(untestedNodes, north) && !nodeVectorContainsPoint(testedNodes, north)) {
                Node *newNode = new Node(*currentNode, north, calculateManhattanDistance(north, target));
                untestedNodes.append(newNode);
            }
        }

        QPoint south = movePointDirection(MovementDirections::GRID_S, currentNode->loc);
        if (isMoveValid(gridMatrix, south)) {
            if (!nodeVectorContainsPoint(untestedNodes, south) && !nodeVectorContainsPoint(testedNodes, south)) {
                Node *newNode = new Node(*currentNode, south, calculateManhattanDistance(south, target));
                untestedNodes.append(newNode);
            }
        }

        QPoint west = movePointDirection(MovementDirections::GRID_W, currentNode->loc);
        if (isMoveValid(gridMatrix, west)) {
            if (!nodeVectorContainsPoint(untestedNodes, west) && !nodeVectorContainsPoint(testedNodes, west)) {
                Node *newNode = new Node(*currentNode, west, calculateManhattanDistance(west, target));
                untestedNodes.append(newNode);
            }
        }

        QPoint east = movePointDirection(MovementDirections::GRID_E, currentNode->loc);
        if (isMoveValid(gridMatrix, east)) {
            if (!nodeVectorContainsPoint(untestedNodes, east) && !nodeVectorContainsPoint(testedNodes, east)) {
                Node *newNode = new Node(*currentNode, east, calculateManhattanDistance(east, target));
                untestedNodes.append(newNode);
            }
        }

        if (untestedNodes.size() == 0) {
            qDebug() << "Tested every location, no path found";
            return false;
        }
    }

    return false;
}

bool PathFinder::nodeVectorContainsPoint(QVector<Node *> vec, QPoint point)
{
    for (int i = 0; i < vec.size(); i++) {
        if (vec.at(i)->loc == point)
            return true;
    }
    return false;
}

bool PathFinder::isMoveValid(GridMatrix *gridMatrix, QPoint point)
{
    // If in bounds, can then check square
    if (point.x() >= 0 && point.x() < gridMatrix->rows() && point.y() >= 0 && point.y() < gridMatrix->columns()) {
        return !gridMatrix->at(point)->getBlocked();
    }
    return false;
}


QPoint PathFinder::movePointDirection(MovementDirections direction, QPoint point, int changeLength)
{
    if (direction == MovementDirections::GRID_W) {
        return QPoint(point.x() - changeLength, point.y());
    } else if (direction == MovementDirections::GRID_E) {
        return QPoint(point.x() + changeLength, point.y());
    } else if (direction == MovementDirections::GRID_N) {
        return QPoint(point.x(), point.y() - changeLength);
    } else if (direction == MovementDirections::GRID_S) {
        return QPoint(point.x(), point.y() + changeLength);
    } else if (direction == MovementDirections::GRID_NW) {
        return QPoint(point.x() - changeLength, point.y() - changeLength);
    } else if (direction == MovementDirections::GRID_SW) {
        return QPoint(point.x() - changeLength, point.y() + changeLength);
    } else if (direction == MovementDirections::GRID_NE) {
        return QPoint(point.x() + changeLength, point.y() - changeLength);
    } else if (direction == MovementDirections::GRID_SE) {
        return QPoint(point.x() + changeLength, point.y() + changeLength);
    }
    throw "Unknown movement direction";
}

// Distance estimation: Manhattan Distance - https://xlinux.nist.gov/dads/HTML/manhattanDistance.html
int PathFinder::calculateManhattanDistance(QPoint p1, QPoint p2)
{
    return qFabs(p1.x() - p2.x()) + qFabs(p1.y() - p2.y());
}


