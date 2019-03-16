#include "ult1.h"

ult1::ult1()
{

}

ult1::~ult1(){

}

void ult1::fly()
{
    setPos(x()-2, y() + 3);
    if(y() > 831) {
        this->scene()->removeItem(this);
        delete this;
    }
}

void ult1::fly2()
{
    setPos(x()+2, y() + 3);
    if(y() > 831) {
        this->scene()->removeItem(this);
        delete this;
    }
}
