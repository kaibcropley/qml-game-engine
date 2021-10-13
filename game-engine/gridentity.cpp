#include "gridentity.h"
#include <QtMath>

//GridEntity::GridEntity(QObject *parent) : QObject(parent)
//{

//}

GridEntity::GridEntity(QQuickItem *parent, int startX, int startY) :
    QQuickItem(parent),
    m_gridX(startX),
    m_gridY(startY)
{
}

GridEntity::GridEntity(const GridEntity &other) :
    QQuickItem(0)
{
    this->m_gridX = other.m_gridX;
    this->m_gridY = other.m_gridY;
}

GridEntity GridEntity::operator=(const GridEntity& other)
{

    this->m_gridX = other.m_gridX;
    this->m_gridY = other.m_gridY;
    return *this;
}

int GridEntity::getGridX()
{
    return m_gridX;
}

void GridEntity::setGridX(int newX)
{
    if (m_gridX != newX) {
        m_gridX = newX;
        emit onGridXChanged(newX);
    }
}

int GridEntity::getGridY()
{
    return m_gridY;
}

void GridEntity::setGridY(int newY)
{
    if (m_gridY != newY) {
        m_gridY = newY;
        emit onGridYChanged(newY);
    }
}

void GridEntity::followPath(int maxSteps)
{
    followPath(maxSteps, m_path);
}

void GridEntity::followPath(int maxSteps, QVector<MovementDirections> &path)
{
    int currSteps = 0;
    QVectorIterator<MovementDirections> pathSteps(path);
    while (pathSteps.hasNext() && currSteps < maxSteps && pathHasSteps()) {
        step(pathSteps.next());
        path.pop_front();
        currSteps++;
    }
}

bool GridEntity::step(MovementDirections direction)
{
    qDebug() << "Stepping" << direction;
    int newX = getGridX();
    int newY = getGridY();

    if (direction == MovementDirections::GRID_W || direction == MovementDirections::GRID_NW || direction == MovementDirections::GRID_SW) {
        newX = newX - 1;
    } else if (direction == MovementDirections::GRID_E || direction == MovementDirections::GRID_NE || direction == MovementDirections::GRID_SE) {
        newX = newX + 1;
    }

    if (direction == MovementDirections::GRID_N || direction == MovementDirections::GRID_NE || direction == MovementDirections::GRID_NW) {
        newY = newY - 1;
    } else if (direction == MovementDirections::GRID_S || direction == MovementDirections::GRID_SE || direction == MovementDirections::GRID_SW) {
        newY = newY + 1;
    }

    return moveTo(newX, newY);
}

// TODO remove return or give it a use
bool GridEntity::moveTo(int newX, int newY)
{
    setGridX(newX);
    setGridY(newY);
    return false;
}

bool GridEntity::pathHasSteps()
{
    return m_path.size() > 0;
}

void GridEntity::findPath(QVector<QVector<GridSquareData *>> gameBoard, int targetX, int targetY)
{
    if (gameBoard.size() < 1) {
        qDebug() << "findPath received invalid gameboard";
        return;
    }
    qDebug() << "findPath( gameBoard," << targetX << ","  <<targetY << ")";
    dijkstra(&gameBoard, QPoint(0,0), QPoint(targetX, targetY));

//    m_path.clear();
//    if (findNextPathStep(&gameBoard, getGridX(), getGridY(), targetX, targetY)) {
//        qDebug() << "GridEntity::findPath Found path!";
////        qDebug() << m_path;
//    } else {
//        qDebug() << "GridEntity::findPath No path found";
//    }
}

// Dumb path finder
//if (currX == targetX && currY == targetY) {
//    return true;
//}
//qDebug() << "findNextPathStep(gameBoard," << currX << currY << targetX <<  targetY;
//gameBoard->at(currX).at(currY)->setVisited(true);

//int newX = currX;
//int newY = currY;

//if (canMoveTo(gameBoard, currX, currY - 1)) {
//    newY--;
//    m_path.append(MovementDirections::GRID_N);
//} else if (canMoveTo(gameBoard, currX, currY + 1)) {
//    newY++;
//    m_path.append(MovementDirections::GRID_S);
//} else if (canMoveTo(gameBoard, currX - 1, currY)) {
//    newX--;
//    m_path.append(MovementDirections::GRID_W);
//} else if (canMoveTo(gameBoard, currX + 1, currY)) {
//    newX++;
//    m_path.append(MovementDirections::GRID_E);
//} else {
//    return false;
//}

bool GridEntity::findNextPathStep(QVector<QVector<GridSquareData *>> *gameBoard, int currX, int currY, int targetX, int targetY)
{

    if (currX == targetX && currY == targetY) {
        return true;
    }
    qDebug() << "findNextPathStep(gameBoard," << currX << currY << targetX <<  targetY;
    gameBoard->at(currX).at(currY)->setVisited(true);


    int newX = currX;
    int newY = currY;

//    if (canMoveTo(gameBoard, currX, currY - 1)) {
//        newY--;
//        m_path.append(MovementDirections::GRID_N);
//    }
//    if (canMoveTo(gameBoard, currX, currY + 1)) {
//        newY++;
//        m_path.append(MovementDirections::GRID_S);
//    }
//    if (canMoveTo(gameBoard, currX - 1, currY)) {
//        newX--;
//        m_path.append(MovementDirections::GRID_W);
//    }
//    if (canMoveTo(gameBoard, currX + 1, currY)) {
//        newX++;
//        m_path.append(MovementDirections::GRID_E);
//    }

//    qDebug() << "findNextPathStep(gameBoard," << currX << currY << targetX <<  targetY << ") Taking step:" << m_path.back();
    return findNextPathStep(gameBoard, newX, newY, targetX, targetY);
}

struct Node {
    Node const *parent;
    QPoint loc;
    int g = 1;
    int h;
    int f;

    Node()
    {
        qDebug() << "SOMEONE IS INCORRECTLY GENERATING NODES";
    }

    Node(QPoint source, QPoint current, QPoint target)
    {
        // Distance estimation: Manhattan Distance - https://xlinux.nist.gov/dads/HTML/manhattanDistance.html
        // G = the movement cost to move from the starting point A to a given square on the grid
        g = 1; //For now use 1 //qFabs(source.x() - current.x()) + qFabs(source.y() - current.y());
        // H = the estimated movement cost to move from that given square on the grid to the final destination
        h = qFabs(source.x() - target.x()) + qFabs(source.y() - target.y());

        f = g + h;
        loc = current;
    }

    Node(Node const *par, QPoint source, QPoint current, QPoint target)
    {
        parent = par;
        // Distance estimation: Manhattan Distance - https://xlinux.nist.gov/dads/HTML/manhattanDistance.html
        // G = the movement cost to move from the starting point A to a given square on the grid
        g = par->g + 1; //qFabs(source.x() - current.x()) + qFabs(source.y() - current.y());
        // H = the estimated movement cost to move from that given square on the grid to the final destination
        h = qFabs(source.x() - target.x()) + qFabs(source.y() - target.y());

        f = g + h;
        loc = current;
    }

    bool operator ==(const Node &other) const
    {
        return loc == other.loc; //&& g == other.g && h == other.h && f == other.f;
    }
};

QPoint GridEntity::movePointDirection(MovementDirections direction, QPoint p, int changeLength)
{
    if (direction == MovementDirections::GRID_W) {
        return QPoint(p.x() - changeLength, p.y());
    } else if (direction == MovementDirections::GRID_E) {
        return QPoint(p.x() + changeLength, p.y());
    } else if (direction == MovementDirections::GRID_N) {
        return QPoint(p.x(), p.y() - changeLength);
    } else if (direction == MovementDirections::GRID_S) {
        return QPoint(p.x(), p.y() + changeLength);
    } else if (direction == MovementDirections::GRID_NW) {
        return QPoint(p.x() - changeLength, p.y() - changeLength);
    } else if (direction == MovementDirections::GRID_SW) {
        return QPoint(p.x() - changeLength, p.y() + changeLength);
    } else if (direction == MovementDirections::GRID_NE) {
        return QPoint(p.x() + changeLength, p.y() - changeLength);
    } else if (direction == MovementDirections::GRID_SE) {
        return QPoint(p.x() + changeLength, p.y() + changeLength);
    }
    qDebug() << "Incorrect direction passed";
//    return null;
}

// Dijkstra's algorithm for pathfinding
//  https://wiki.jmonkeyengine.org/docs/3.3/contributions/_attachments/Astar.pdf
bool GridEntity::dijkstra(QVector<QVector<GridSquareData *>> *gameBoard, QPoint source, QPoint target)
{
    Node *startNode = new Node(source, source, target);

    QVector<Node> unvisitedSquares; // open list
    QVector<Node> visitedSquares; //closed list
    unvisitedSquares.append(*startNode);

    Node current = *startNode;

    while (unvisitedSquares.size() > 0)
    {
        if (current.loc == target) {
            qDebug() << "Success!!!";
            return true;
        }

        Node lowest = unvisitedSquares.at(0);
        int lowestIndex = 0;
        for (int i = 0; i < unvisitedSquares.size(); i++) {
            if (lowest.f > unvisitedSquares.at(i).f) {
                lowest = unvisitedSquares.at(i);
                lowestIndex = i;
            }
        }
        current = lowest;
        visitedSquares.append(lowest);
        unvisitedSquares.remove(lowestIndex);

//        qDebug() << "Visited locations";
//        for (int i = 0; i < visitedSquares.size(); i++) {
//            qDebug() << "    Point:" << visitedSquares.at(i).loc;
//        }

        // Nodes
        QPoint north = movePointDirection(MovementDirections::GRID_N, current.loc);
        QPoint south = movePointDirection(MovementDirections::GRID_S, current.loc);
        QPoint west = movePointDirection(MovementDirections::GRID_W, current.loc);
        QPoint east = movePointDirection(MovementDirections::GRID_E, current.loc);
        qDebug() << "Current:" << current.loc;
        qDebug() << "All points around current" << north << south << west << east;

        // Add intial possible movement options
        if (canMoveTo(gameBoard, north)) {
            Node newNode(&current, source, north, target);
            if (!unvisitedSquares.contains(newNode) && !visitedSquares.contains(newNode)) {
                unvisitedSquares.append(newNode);
            }
        }
        if (canMoveTo(gameBoard, south)) {
            Node newNode(&current, source, south, target);
            if (!unvisitedSquares.contains(newNode) && !visitedSquares.contains(newNode)) {
                unvisitedSquares.append(newNode);
            }
//            unvisitedSquares.append(Node(source, south, target));
        }
        if (canMoveTo(gameBoard, west)) {
            Node newNode(&current, source, west, target);
            if (!unvisitedSquares.contains(newNode) && !visitedSquares.contains(newNode)) {
                unvisitedSquares.append(newNode);
            }
        }
        if (canMoveTo(gameBoard, east)) {
            Node newNode(&current, source, east, target);
            if (!unvisitedSquares.contains(newNode) && !visitedSquares.contains(newNode)) {
                unvisitedSquares.append(newNode);
            }
//            unvisitedSquares.append(Node(source, east, target));
        }

        if (unvisitedSquares.size() == 0) {
            qDebug() << "Tested every location";
            return false;
        }
    }

    return false;
    delete startNode;
}

GridSquareData * GridEntity::getValue(QVector<QVector<GridSquareData *>> *gameBoard, int x, int y)
{
    return gameBoard->at(x).at(y);
}

bool GridEntity::canMoveTo(QVector<QVector<GridSquareData *>> *gameBoard, QPoint point)
{
    // If in bounds, can then check square
    if (point.x() >= 0 && point.x() < gameBoard->size() && point.y() >= 0 && point.y() < gameBoard->at(point.x()).size()) {
        qDebug() << "Testing in bounds" << point;
        return canMoveTo(gameBoard->at(point.x()).at(point.y()));
    }
    qDebug() << "Out of bounds:" << point;
    return false;
}

bool GridEntity::canMoveTo(GridSquareData *square)
{
    return !square->getBlocked() && !square->getVisited();
}



