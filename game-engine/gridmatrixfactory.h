#ifndef GRIDMATRIXFACTORY_H
#define GRIDMATRIXFACTORY_H

#include "gridmatrix.h"

class GridMatrixFactory
{
public:
    GridMatrixFactory();

    GridMatrix* createRandomMatrix(int rows, int columns);

private:
    int getRandomInt();
};

#endif // GRIDMATRIXFACTORY_H
