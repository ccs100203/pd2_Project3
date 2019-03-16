#ifndef BOSS1_H
#define BOSS1_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QDebug>
#include "monster.h"
#include <QProgressBar>

class boss1 : public monster
{
    Q_OBJECT
public:
    int hp=2000;
    boss1();
    virtual ~boss1();
    QProgressBar *line;

public slots:
    virtual void fly();
    virtual int qte();
};

#endif // BOSS1_H
