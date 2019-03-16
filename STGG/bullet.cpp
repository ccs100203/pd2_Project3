#include "bullet.h"

bullet::bullet()
{

}
bullet::~bullet()
{

}
int bullet::choose =0;
void bullet::fly()
{
    setPos(x(), y() - 4);
    if(choose==1){
        setTransform(QTransform().rotate(rotate,Qt::YAxis));
        rotate++;
    }
    if(choose==2){
        setTransform(QTransform().rotate(rotate,Qt::ZAxis));
        rotate++;
    }
    if(y() < 0){
        this->scene()->removeItem(this);
        delete this;
    }
}
