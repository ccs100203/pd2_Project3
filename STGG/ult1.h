#ifndef ULT1_H
#define ULT1_H


#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QDebug>

class ult1 : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    ult1();
    ~ult1();
    int times=0;

public slots:
    virtual void fly();
    virtual void fly2();
};

#endif // ULT1_H
