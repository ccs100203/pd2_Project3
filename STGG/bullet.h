#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTransform>

class bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    bullet();
    virtual ~bullet();
    int rotate;
    static int choose;
public slots:
    virtual void fly();
};

#endif // BULLET_H
