#ifndef GRIDMATRIX_H
#define GRIDMATRIX_H

#include <QObject>
#include "gridsquaredata.h"

class GridMatrix : public QObject
{
    Q_OBJECT
public:
    explicit GridMatrix(QObject *parent = 0, int rows = 10, int columns = 10);
    GridMatrix(GridMatrix &other);

    void setMatrix(QVector<QVector<GridSquareData *>> *newBoard);
    QVector<QVector<GridSquareData *>> getMatrix();

    Q_INVOKABLE GridSquareData* at(QPoint p);
    Q_INVOKABLE GridSquareData* at(int x, int y);

    int rows();
    int columns();

    Q_INVOKABLE QVariantMap getSquareMap(int x, int y);
    Q_INVOKABLE QVariant matrixToOneDimension();

    Q_INVOKABLE bool setSquare(GridSquareData *newSquare);

signals:

public slots:

private:
    QVector<QVector<GridSquareData *>> *m_matrix;
};

#endif // GRIDBOARD_H
