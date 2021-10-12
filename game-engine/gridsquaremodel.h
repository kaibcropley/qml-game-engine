#ifndef GRIDSQUAREMODEL_H
#define GRIDSQUAREMODEL_H

#include <QObject>
#include <QAbstractListModel>

class GridSquareModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit GridSquareModel(QObject *parent = 0);

signals:

public slots:
};

#endif // GRIDSQUAREMODEL_H
