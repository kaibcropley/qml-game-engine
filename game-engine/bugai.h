#ifndef BUGAI_H
#define BUGAI_H

#include <QObject>
#include <QPoint>

class BugAi : public QObject
{
    Q_OBJECT
public:
    explicit BugAi(QObject *parent = 0);

    void plan();

signals:
    void move(QPoint targetPoint);

private:
//    int hunger_level;

};

#endif // BUGAI_H
