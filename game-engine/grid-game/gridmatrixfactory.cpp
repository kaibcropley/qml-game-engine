#include "gridmatrixfactory.h"

GridMatrixFactory::GridMatrixFactory()
{

}

GridMatrix* GridMatrixFactory::createRandomMatrix(int rows, int columns)
{
    qDebug() << "GridMatrixFactory::createRandomMatrix(" << rows << "," << columns << ")";
    GridMatrix *gridMatrix = new GridMatrix();
    if (gridMatrix->rows() == 0) {

        QVector<QVector<GridSquareData *>> *grid = new QVector<QVector<GridSquareData *>>;

        for(int i = 0; i < rows; i++) // Initialize starting with row by row
        {
            QVector<GridSquareData *> currRow;
            for(int x = 0; x < columns; x++)
            {
                GridSquareData *newSquare = new GridSquareData(0, QPoint(i, x));
//                newSquare->setSquareType(static_cast<GridSquareData::BoardSquareType>((getRandomInt() % 2)));
                if (x != 0 && x != columns && i != 0 && i != rows) {
                    newSquare->setMovementAllowed((getRandomInt() % 5) != 0);
                }
                if (newSquare->getMovementAllowed()) {
                    newSquare->setContainsFood((getRandomInt() % 5) == 1);
                } else {
                    newSquare->setContainsFood(false);
                }
                currRow.append(newSquare);
            }
            grid->append(currRow);
        }
        gridMatrix->setMatrix(grid);
    }
    return gridMatrix;
}

int GridMatrixFactory::getRandomInt()
{
    return rand();
}
