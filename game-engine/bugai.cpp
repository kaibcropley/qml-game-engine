#include "bugai.h"
#include "QDebug"

BugAi::BugAi(QObject *parent) : QObject(parent)
{

}

void BugAi::plan()
{
    qDebug() << "BugAi::plan() Faking movement target";
    move(QPoint(5,4));
}
