#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(0, 0, 750,830)), //1141,831
    timer(new QTimer)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    player = new QGraphicsPixmapItem(QPixmap(":/res/plane.png").scaled(55,45));
    scene->addItem(player);
    player->setPos(350-player->pixmap().width()/2, 830-player->pixmap().height());
    timer->start(10);
    setWindowTitle("STG");
    //window()->setStyleSheet("blue");
    //scene->setBackgroundBrush(QBrush(Qt::white));
    scene->setBackgroundBrush(QPixmap(":/res/background1.png").scaled(scene->width(),scene->height()));


    srand(time(NULL));
    connect(timer, SIGNAL(timeout()), this, SLOT(shoot()));
    connect(timer, SIGNAL(timeout()), this, SLOT(product_mons()));
    connect(timer, SIGNAL(timeout()), this, SLOT(life()));
    connect(timer, SIGNAL(timeout()), this, SLOT(follow()));
    QPixmap p(":/res/plane.png");
    QPixmap m(":/res/monster1.png");
    QPixmap x(":/res/X.png");
    QPixmap s(":/res/rightsaber.png");
    hp1 = new QLabel(this);
    hp1->setGeometry(800,180,50,50);
    hp1->setPixmap(p.scaled(50,50));
    hp2 = new QLabel(this);
    hp2->setGeometry(865,180,50,50);
    hp2->setPixmap(p.scaled(50,50));
    hp3 = new QLabel(this);
    hp3->setGeometry(930,180,50,50);
    hp3->setPixmap(p.scaled(50,50));
    hp4 = new QLabel(this);
    hp4->setGeometry(995,180,50,50);
    hp4->setPixmap(p.scaled(50,50));
    hp5 = new QLabel(this);
    hp5->setGeometry(1060,180,50,50);
    hp5->setPixmap(p.scaled(50,50));
    score = new QLCDNumber(this);
    score->setGeometry(855,70,200,40);
    score->setPalette(Qt::yellow);
    score->setDigitCount(10);
    gametime = new QLCDNumber(this);
    gametime->setGeometry(855,550,140,70);
    gametime->setPalette(Qt::blue);
    gametime->setDigitCount(5);
    mons_photo = new QLabel(this);
    mons_photo->setGeometry(800,360,120,120);
    mons_photo->setPixmap(m.scaled(120,120));
    X_1 = new QLabel(this);
    X_1->setGeometry(930,405,40,40);
    X_1->setPixmap(x.scaled(40,40));
    mons_num = new QLabel(this);
    mons_num->setGeometry(1015,385,150,80);
    mons_num->setText(QString::number(monster::kills));
    mons_num->setStyleSheet("font:bold 80px");
    r_saber = new QLabel(this);
    r_saber->setGeometry(800,645,180,180);
    r_saber->setPixmap(s.scaled(180,180));
    saber_hp = new QLabel(this);
    saber_hp->setGeometry(980,740,160,40);
    saber_hp->setText(QString::number(saber->hp));
    saber_hp->setStyleSheet("font:bold 40px");

    //score->display(1234567890);
    //score->display(sh);
    //QList<QGraphicsItem *> list = scene->collidingItems(player);
    //if(!scene->collidingItems(player).isEmpty()) hp1->hide();
    //else hp2->hide();
    cheat = new QPushButton(this);
    cheat->setGeometry(820,270,90,60);
    cheat->setText("Cheat Dog");
    cheat->setStyleSheet("background-color:mistyrose; font-size:15px; font-style:garamond");
    connect(cheat, SIGNAL(clicked(bool)), this, SLOT(Scheat()));
    rotatebullet = new QPushButton(this);
    rotatebullet->setGeometry(940,270,90,60);
    rotatebullet->setText("Rotate!");
    rotatebullet->setStyleSheet("background-color:violet; font-size:15px");
    connect(rotatebullet, SIGNAL(clicked(bool)), this, SLOT(Srotate()));

    saber = new boss1;
    saber->setPixmap(QPixmap(":/res/saber.png").scaled(123,100));
    saber->setPos(370, 30);
    saber->connect(timer, SIGNAL(timeout()), saber, SLOT(fly()));
    scene->addItem(static_cast<QGraphicsPixmapItem*>(saber));
    saber->line = new QProgressBar(this);
    saber->line->setGeometry(15,16,750,10);
    saber->line->setRange(0,2000);
    //saber->line->setStyleSheet("QProgressBar:chunk{background-color:blue}");
    //saber->line->setFormat("");
    through = new QTime(0,0,0);
    connect(this, SIGNAL(checkdie()), this, SLOT(saberdie()));

    //b->setZValue(1);
    //mons->setZValue(2);
    //b2->setZValue(3);
    //saberult->setZValue(3);
    player->setZValue(4);
    saber->setZValue(5);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()) {
    case Qt::Key_Up:
    case Qt::Key_W:
        //if(player->y()>0) player->setPos(player->x(), player->y() - 10);
        w=1;
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        //if(player->y()<755) player->setPos(player->x(), player->y() + 12);
        s=1;
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        //if(player->x()>0) player->setPos(player->x() - 15, player->y());
        a=1;
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        //if(player->x()<653) player->setPos(player->x() + 15, player->y());
        d=1;
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    switch(e->key()) {
    case Qt::Key_Up:
    case Qt::Key_W:
        w=0;
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        s=0;
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        a=0;
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        d=0;
        break;
    }
}

/*void MainWindow::mousePressEvent(QMouseEvent *e)
{
    bullet *b = new bullet;

    b->setPixmap(QPixmap(":/res/bullet.jpg").scaled(20,40));
    b->setPos(player->x() + player->pixmap().width() / 2 - b->pixmap().width() / 2, player->y() - b->pixmap().height());
    b->connect(timer, SIGNAL(timeout()), b, SLOT(fly()));
    scene->addItem(static_cast<QGraphicsPixmapItem*>(b));
}*/

void MainWindow::shoot(){
    //b->setZValue(1);
    //mons->setZValue(2);
    //b2->setZValue(3);
    //saberult->setZValue(3);

    if(sh%10==0){
        b = new bullet;
        b->setPixmap(QPixmap(":/res/bullet.png").scaled(15,30));
        b->setPos(player->x() + player->pixmap().width() / 2 - b->pixmap().width() / 2, -10+player->y() - b->pixmap().height());
        b->connect(timer, SIGNAL(timeout()), b, SLOT(fly()));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(b));
        b->setZValue(1);
    }
    if(sh%120==0 && saber->hp>0){ //saber attack
        b2 = new bullet_b1;
        b2->setPixmap(QPixmap(":/res/saberatk.png").scaled(183,120));
        b2->setPos(saber->x() + saber->pixmap().width() / 2 - b2->pixmap().width() / 2, saber->y() + 30);
        b2->connect(timer, SIGNAL(timeout()), b2, SLOT(fly()));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(b2));
        b2->setZValue(3);
    }

    if(saber->hp<1200 && saber->hp>10 && sh%120==0){
        saberult = new ult1;
        saberult->setPixmap(QPixmap(":/res/saberult.png").scaled(101,150));
        saberult->setPos(600,10);
        saberult->connect(timer, SIGNAL(timeout()), saberult, SLOT(fly()));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(saberult));
        saberult->setZValue(3);
    }
    if(saber->hp<900 && saber->hp>500 && (sh+20)%140==0){
        saberult = new ult1;
        saberult->setPixmap(QPixmap(":/res/saberult.png").scaled(101,150));
        saberult->setPos(600,110);
        saberult->connect(timer, SIGNAL(timeout()), saberult, SLOT(fly()));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(saberult));
        saberult->setZValue(3);
    }
    if(saber->hp<600 && saber->hp>10 && sh%110==0){
        saberult = new ult1;
        saberult->setPixmap(QPixmap(":/res/saberult.png").scaled(135,200));
        saberult->setPos(600,220);
        saberult->connect(timer, SIGNAL(timeout()), saberult, SLOT(fly()));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(saberult));
        saberult->setZValue(3);
    }
    if(saber->hp<900 && saber->hp>10 && sh%140==0){
        saberult = new ult1;
        saberult->setPixmap(QPixmap(":/res/saberult2.png").scaled(101,150));
        saberult->setPos(0,110);
        saberult->connect(timer, SIGNAL(timeout()), saberult, SLOT(fly2()));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(saberult));
        saberult->setZValue(3);
    }
    if(saber->hp<1100 && saber->hp>10 && (sh+20)%110==0){
        saberult = new ult1;
        saberult->setPixmap(QPixmap(":/res/saberult2.png").scaled(135,200));
        saberult->setPos(100,10);
        saberult->connect(timer, SIGNAL(timeout()), saberult, SLOT(fly2()));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(saberult));
        saberult->setZValue(3);
    }

}

void MainWindow::product_mons(){

    if(sh%40==0){
        mons = new monster('a');
        //if(!scene->collidingItems(mons).isEmpty()) qDebug()<< 444<<endl;
        mons->setPixmap(QPixmap(":/res/monster1.png").scaled(110,110));
        mons->setPos(rand()%620+1, 20);
        mons->connect(timer, SIGNAL(timeout()), mons, SLOT(fly()));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(mons));
        mons->setZValue(2);
    }

}

void MainWindow::paintEvent(QPaintEvent *){
    //scene->addLine(750,831,750,0);
}

void MainWindow::life(){
    if(cdhp == sh-300) invin=1; //撞到後無敵三秒
    if(invin){
        if(!scene->collidingItems(player).isEmpty()) {
            hp--; //扣血
            grade-=5000; //扣分
            invin = 0; //進入僵直
            player->setPos(350-player->pixmap().width()/2, 830-player->pixmap().height()); //回歸原點
            cdhp = sh; //計算僵直(無敵)
        }
        if(hp<1) hp5->hide();
        else if(hp<2) hp4->hide();
        else if(hp<3) hp3->hide();
        else if(hp<4) hp2->hide();
        else if(hp<5) hp1->hide();
    }
    if(hp<=0){
        disconnect(timer, SIGNAL(timeout()), this, SLOT(shoot()));
        disconnect(timer, SIGNAL(timeout()), this, SLOT(product_mons()));
        disconnect(timer, SIGNAL(timeout()), this, SLOT(life()));
        disconnect(timer, SIGNAL(timeout()), this, SLOT(follow()));
        cheat->hide();
        rotatebullet->hide();
        end = new QGraphicsPixmapItem(QPixmap(":/res/lose.png").scaled(761,450));
        scene->addItem(end);
        end->setPos(5,50);

    }
}

void MainWindow::Scheat(){
    hp=5;
    hp1->show();
    hp2->show();
    hp3->show();
    hp4->show();
    hp5->show();
    hptimes--;
    cheat->setText("Cheat "+ QString::number(hptimes));
    if(hptimes==0){
        cheat->hide();
    }
}

void MainWindow::follow(){
    sh++;
    grade++;
    score->display(grade);
    grade +=saber->qte();
    saber->line->setValue(saber->hp);
    mons_num->setText(QString::number(monster::kills));
    if(sh%100==0) {
        //QTime time = QTime::currentTime();
        *through = through->addSecs(1);
        QString timetext = through->toString("mm:ss");
        gametime->display(timetext);
    }
    // 飛機大小55,45
    if(w && player->y()>0) player->setPos(player->x(), player->y() - 2);
    if(s && player->y()<785) player->setPos(player->x(), player->y() + 2);
    if(a && player->x()>0) player->setPos(player->x()-2, player->y());
    if(d && player->x()<695) player->setPos(player->x()+2, player->y());

    if(saber->hp<=0) bossshow++;
    if(bossshow==1){
        //emit checkdie();
        diee = new QTimer;
        diee->start(5000);
        connect(diee,SIGNAL(timeout()),this,SLOT(saberdie()));
    }

    saber_hp->setText(QString::number(saber->hp)); //更改saber血量顯示
    /*if(player->collidesWithItem(saber)){ 可行
        qDebug()<< 123<<endl;
    }*/
    /*QList<QGraphicsItem *> list = scene->items();
    QList<QGraphicsItem *> list2;
    QList<QGraphicsItem *> list3;
       foreach(QGraphicsItem * i , list)
       {
            bullet* item= dynamic_cast<bullet *>(i);

            if (item)
            {
                list2.append(i);
                 //qDebug()<< test++<<endl;
                 this->hide();
                 return 0;
             }
        }
    return 0;*/
}

void MainWindow::Srotate(){
    bullet::choose++;
    if(bullet::choose==3) bullet::choose =0;
}

void MainWindow::saberdie(){
    disconnect(timer, SIGNAL(timeout()), this, SLOT(shoot()));
    disconnect(timer, SIGNAL(timeout()), this, SLOT(product_mons()));
    disconnect(timer, SIGNAL(timeout()), this, SLOT(life()));
    disconnect(timer, SIGNAL(timeout()), this, SLOT(follow()));
    cheat->hide();
    rotatebullet->hide();
    end = new QGraphicsPixmapItem(QPixmap(":/res/win.png").scaled(761,450));
    scene->addItem(end);
    end->setPos(5,50);
    delete diee;

    /*archer = new boss1;
    archer->setPixmap(QPixmap(":/res/archer.png").scaled(123,100));
    archer->setPos(370, 30);
    archer->connect(timer, SIGNAL(timeout()), archer, SLOT(fly()));
    scene->addItem(static_cast<QGraphicsPixmapItem*>(archer));
    archer->line = new QProgressBar(this);
    archer->line->setGeometry(15,16,750,10);
    archer->line->setRange(0,500);*/
}
