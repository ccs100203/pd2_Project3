#ifndef MONSTER_H
#define MONSTER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QDebug>
#include "bullet.h"
#include <QProgressBar>
#include <QTimer>

class monster : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    int hp=100;
    int test=0;
    monster();
    monster(char);
    virtual ~monster();
    QProgressBar *line;
    QTimer *timer;
    static int kills;
    bool water =1;

public slots:
    virtual void fly();
    virtual int qte();
};

#endif // MONSTER_H
