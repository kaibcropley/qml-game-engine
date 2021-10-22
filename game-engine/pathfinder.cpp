#include "pathfinder.h"
#include <QtMath>

#include <algorithm>    // std::reverse

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

QVector<QPoint> PathFinder::findPath(GridMatrix *gridMatrix, QPoint source, QPoint target)
{
    if (gridMatrix == nullptr || gridMatrix->rows() < 1 || gridMatrix->columns() < 1) {
//        qDebug() << "PathFinder::findPath: Invalid grid matrix";
        return QVector<QPoint>();
    }

    if (source == target) {
//        qDebug() << "PathFinder::findPath: QPoint source == QPoint target";
        return QVector<QPoint>();
    }

//    qDebug() << "PathFinder::findPath( matrix," << source << "," << target << ")";
    return dijkstra(gridMatrix, source, target);
}

// Dijkstra's algorithm for pathfinding
//  https://wiki.jmonkeyengine.org/docs/3.3/contributions/_attachments/Astar.pdf
//  Current implementation notes
//      The current implementation won'tupdate a grid's parent if we find a faster way to that square, this isn't a big concern with movement being limited to 1 square but will need tweaks later
QVector<QPoint> PathFinder::dijkstra(GridMatrix *gridMatrix, QPoint source, QPoint target)
{
    // Start node can be found by parent == nullptr
    Node *startNode = new Node(source, calculateManhattanDistance(source, target));

    QVector<Node *> untestedNodes; // open list
    QVector<Node *> testedNodes; // closed list
    untestedNodes.append(startNode);

    Node *currentNode = startNode;

    QVector<MovementDirections> movementOptions = {GRID_N, GRID_S, GRID_W, GRID_E, GRID_NW, GRID_NE, GRID_SW, GRID_SE};

    while (untestedNodes.size() > 0)
    {
        if (currentNode->loc == target) {
            QVector<QPoint> path;
            while(currentNode->parent != nullptr) {
                path.append(currentNode->loc);
                currentNode = currentNode->parent;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        Node *lowest = untestedNodes.at(0);
        int lowestIndex = 0;
        for (int i = 0; i < untestedNodes.size(); i++) {
            if (lowest->f > untestedNodes.at(i)->f) {
                lowest = untestedNodes.at(i);
                lowestIndex = i;
            } else if (lowest->f == untestedNodes.at(i)->f) {
                if (untestedNodes.at(i)->loc.y() == target.y() || untestedNodes.at(i)->loc.x() == target.x()) {
                    lowest = untestedNodes.at(i);
                    lowestIndex = i;
                }
            }
        }
        currentNode = lowest;
        testedNodes.append(lowest);
        untestedNodes.remove(lowestIndex);

        QVectorIterator<MovementDirections> pathSteps(movementOptions);
        while (pathSteps.hasNext()) {
            QPoint currPoint = movePointDirection(pathSteps.next(), currentNode->loc);
            if (isMoveValid(gridMatrix, currPoint)) {
                if (!nodeVectorContainsPoint(untestedNodes, currPoint) && !nodeVectorContainsPoint(testedNodes, currPoint)) {
                    Node *newNode = new Node(*currentNode, currPoint, calculateManhattanDistance(currPoint, target));
                    untestedNodes.append(newNode);
                }
            }
        }
    }

    qDebug() << "Tested every location, no path found between points " << source << "and" << target;
    return QVector<QPoint>();
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
        return !gridMatrix->at(point)->getMovementAllowed();
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


