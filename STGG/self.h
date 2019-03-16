#ifndef SELF_H
#define SELF_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class self : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    self();
};

#endif // SELF_H
