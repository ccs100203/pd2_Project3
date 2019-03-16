#include "boss1.h"

boss1::boss1()
{

}

boss1::~boss1(){

}

void boss1::fly()
{
    setPos(x()-1, y());
    if(x()<0) {
        setPos(630,20);
    }
}

int boss1::qte(){
    if(hp<=0){
        this->hide();
        line->hide();
    }/*
    if(hp>0 && !this->collidingItems().isEmpty()){
            hp--;
            //qDebug()<<hp<<endl;
            return 50;

    }
    return 0;*/
    QList<QGraphicsItem *> list = this->collidingItems();

       foreach(QGraphicsItem * i , list)
       {
            bullet* item= dynamic_cast<bullet *>(i);
            if (item&&hp>0)
            {
                hp--;
                //qDebug()<<hp<<endl;
                return 50;
            }
        }
    return 0;
}
