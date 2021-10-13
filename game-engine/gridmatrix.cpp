#include "gridmatrix.h"

GridMatrix::GridMatrix(QObject *parent) : QObject(parent)
{

}

GridMatrix::GridMatrix(GridMatrix &other)
{
    this->setMatrix(other.getMatrix());
}

void GridMatrix::setMatrix(QVector<QVector<GridSquareData *>> newBoard)
{
    m_matrix = newBoard;
}

QVector<QVector<GridSquareData *>> GridMatrix::getMatrix()
{
    return m_matrix;
}

GridSquareData* GridMatrix::at(QPoint p)
{
    return this->at(p.x(), p.y());
}

GridSquareData* GridMatrix::at(int x, int y)
{
    return m_matrix.at(x).at(y);
}

int GridMatrix::rows()
{
    return m_matrix.size();
}

int GridMatrix::columns()
{
    if (m_matrix.size() != 0)
        return m_matrix.at(0).size();
    return 0;
}

