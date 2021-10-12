#include "gridentity.h"

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
    while (pathSteps.hasNext() && currSteps < maxSteps) {
        step(pathSteps.next());
        path.pop_front();
        currSteps++;
    }
    qDebug() << getGridX() << getGridY();
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
    m_path.clear();
    if (findNextPathStep(&gameBoard, getGridX(), getGridY(), targetX, targetY)) {
        qDebug() << "GridEntity::findPath Found path!";
        qDebug() << m_path;
    } else {
        qDebug() << "GridEntity::findPath No path found";
    }
}

bool GridEntity::findNextPathStep(QVector<QVector<GridSquareData *>> *gameBoard, int currX, int currY, int targetX, int targetY)
{

    if (currX == targetX && currY == targetY) {
        return true;
    }
    qDebug() << "findNextPathStep(gameBoard," << currX << currY << targetX <<  targetY;
    gameBoard->at(currX).at(currY)->setVisited(true);

    int newX = currX;
    int newY = currY;

    if (canMoveTo(gameBoard, currX, currY - 1)) {
        newY--;
        m_path.append(MovementDirections::GRID_N);
    } else if (canMoveTo(gameBoard, currX, currY + 1)) {
        newY++;
        m_path.append(MovementDirections::GRID_S);
    } else if (canMoveTo(gameBoard, currX - 1, currY)) {
        newX--;
        m_path.append(MovementDirections::GRID_W);
    } else if (canMoveTo(gameBoard, currX + 1, currY)) {
        newX++;
        m_path.append(MovementDirections::GRID_E);
    } else {
        return false;
    }


//    if (currX < targetX) {
//        newX = currX + 1;
//    } else if (currX > targetX) {
//        newX = currX - 1;
//    }

//    if (currY < targetY) {
//        newY++;
//        if (currX < targetX) {
//            newX = currX + 1;
//        } else if (currX > targetX) {
//            newX = currX - 1;
//        }
//    } else if (currY > targetY) {
//        newY--;
//        if (currX < targetX) {
//            canMoveTo(gameBoard, currX + 1, newY)
//        } else if (currX > targetX) {
//            newX = currX - 1;
//        }
//    }



//    if (currY < targetY) {
//        newY = currY + 1;
//        if (currX < targetX) {
//            newX = currX + 1;
//            m_path.append(MovementDirections::GRID_SE);
//        } else if (currX > targetX) {
//            newX = currX - 1;
//            m_path.append(MovementDirections::GRID_SW);
//        } else {
//            m_path.append(MovementDirections::GRID_S);
//        }
//    } else if (currY > targetY) {
//        newY = currY - 1;
//        if (currX < targetX) {
//            newX = currX + 1;
//            m_path.append(MovementDirections::GRID_NE);
//        } else if (currX > targetX) {
//            newX = currX - 1;
//            m_path.append(MovementDirections::GRID_NW);
//        } else {
//            m_path.append(MovementDirections::GRID_N);
//        }
//    } else {
//        if (currX < targetX) {
//            newX = currX + 1;
//            m_path.append(MovementDirections::GRID_E);
//        } else if (currX > targetX) {
//            newX = currX - 1;
//            m_path.append(MovementDirections::GRID_W);
//        }
//    }

//    qDebug() << "findNextPathStep(gameBoard," << currX << currY << targetX <<  targetY << ") Taking step:" << m_path.back();
    return findNextPathStep(gameBoard, newX, newY, targetX, targetY);
}
bool GridEntity::canMoveTo(GridSquareData *square)
{
    return !square->getBlocked() && !square->getVisited();
}

bool GridEntity::canMoveTo(QVector<QVector<GridSquareData *>> *gameBoard, int x, int y)
{
    if (x >= 0 && x < gameBoard->size() && y >= 0 && y < gameBoard->at(x).size()) {
        return canMoveTo(gameBoard->at(x).at(y));
    }
    return false;
}



