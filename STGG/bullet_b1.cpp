#include "bullet_b1.h"

bullet_b1::bullet_b1()
{

}

bullet_b1::~bullet_b1(){

}


void bullet_b1::fly(){
    setPos(x(), y() + 2);
    if(y() > 830) {
        this->scene()->removeItem(this);
        delete this;
    }
}
