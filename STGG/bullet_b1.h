#ifndef BULLET_B1_H
#define BULLET_B1_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class bullet_b1 : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    bullet_b1();
    virtual ~bullet_b1();

public slots:
    virtual void fly();
};


#endif // BULLET_B1_H
