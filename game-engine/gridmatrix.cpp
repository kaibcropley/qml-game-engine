#include "gridmatrix.h"

GridMatrix::GridMatrix(QObject *parent) :
    QObject(parent),
    m_matrix(nullptr)
{

}

GridMatrix::GridMatrix(GridMatrix &other)
{
    this->m_matrix = other.m_matrix;
}

void GridMatrix::setMatrix(QVector<QVector<GridSquareData *>> *newBoard)
{
    m_matrix = newBoard;
}

QVector<QVector<GridSquareData *>> GridMatrix::getMatrix()
{
    return *m_matrix;
}

GridSquareData* GridMatrix::at(QPoint p)
{
    return this->at(p.x(), p.y());
}

GridSquareData* GridMatrix::at(int x, int y)
{
    return m_matrix->at(x).at(y);
}

int GridMatrix::rows()
{
    if (m_matrix != nullptr)
        return m_matrix->size();
    return 0;
}

int GridMatrix::columns()
{
    if (m_matrix->size() != 0)
        return m_matrix->at(0).size();
    return 0;
}

// Returns a QVariantMap/JSON obj with data for the UI
QVariantMap GridMatrix::getSquareMap(int x, int y)
{
    return at(x,y)->toQVariantMap();
}

// Returns an array of QVariantMap/JSON objects as one long array for the grid repeater
QVariant GridMatrix::matrixToOneDimension()
{
    QVariantList oneDimensionalBoard;
    for(int y = 0; y < rows(); y++){
        for(int x = 0; x < columns(); x++) {
            oneDimensionalBoard.append(getSquareMap(x, y));
        }
    }
    return QVariant::fromValue(oneDimensionalBoard);
}
