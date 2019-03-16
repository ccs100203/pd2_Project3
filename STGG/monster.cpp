#include "monster.h"

monster::monster(char)
{
    timer = new QTimer;
    timer->start(10);
    connect(timer,SIGNAL(timeout()),this,SLOT(qte()));

}

monster::monster(){

}
monster::~monster()
{

}


void monster::fly()
{
    setPos(x(), y() + 2);
    if(y() > 830) {
        this->scene()->removeItem(this);
        delete this;
    }
}
int monster::kills=0;
int monster::qte(){

    QList<QGraphicsItem *> list = this->collidingItems();

       foreach(QGraphicsItem * i , list)
       {
            bullet* item= dynamic_cast<bullet *>(i);
            if (item && rand()%30<1)
            {
                 //qDebug()<< test++<<endl;
                if(water){
                    kills++;
                    water = false;
                }
                //this->hide();
                this->scene()->removeItem(this);
                delete this;
                return 0;
             }
        }
    return 0;
}
