#include "gridmatrix.h"

GridMatrix::GridMatrix(QObject *parent, int rows, int columns) :
    QObject(parent),
    m_matrix(nullptr)
{
    m_matrix = new QVector<QVector<GridSquareData *>>;

    for(int i = 0; i < rows; i++) // Initialize starting with row by row
    {
        QVector<GridSquareData *> currRow(columns, nullptr);
        m_matrix->append(currRow);
    }
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
    if (rows() != 0)
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

bool GridMatrix::setSquare(GridSquareData *newSquare) {
    QPoint gridPos = newSquare->getGridPos();
    if (at(gridPos) != nullptr) {
        qDebug() << "GridMatrix::setSquare Duplicate Grid Square" << gridPos;
        return false;
    } else if (m_matrix == nullptr) {
        qDebug() << "GridMatrix::setSquare No matrix" << gridPos;
        return false;
    }

    // Unsure yet why [] syntax always requires a leading [0], but must use it over .at because it returns a const reference
    m_matrix[0][gridPos.x()][gridPos.y()] = newSquare;
    return true;
}
