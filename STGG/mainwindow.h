#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTime>
#include <QTimer>
#include <cstdlib>
#include "bullet.h"
#include "monster.h"
#include "boss1.h"
#include "ult1.h"
#include "bullet_b1.h"
#include <QDebug>
#include <QKeyEvent>
#include <QPainter>
#include <QLabel>
#include <QLCDNumber>
#include <QPushButton>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int sh=0,grade=0; //sh是隨著time跑的變數 grade是成績
    void paintEvent(QPaintEvent *);
    int hp=5,cdhp=0; //HP玩家血量  CDHP是被打到的僵直時間
    bool invin=1; //設定是否進入僵直(無敵)
    int test=0;
    int hptimes=3; //hp回復限制
    bool w=0,a=0,s=0,d=0; //上下左右
    int bossshow=0;
    QLabel *hp1,*hp2,*hp3,*hp4,*hp5; //血量顯示
    QLabel *mons_photo, *X_1, *mons_num;
    QLabel *r_saber, *saber_hp; //右邊的SABER圖示
    QLCDNumber *score,*gametime; //分數跟遊戲時間
    QPushButton *cheat, *rotatebullet; //cheat是補血
    monster *mons; //怪物產生
    bullet *b; //b玩家子彈
    bullet_b1 *b2; //b2 saber子彈
    boss1 *saber, *archer;
    ult1 *saberult; //saber大絕


signals:
    void checkdie();


public slots:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void keyReleaseEvent(QKeyEvent *e);
    //virtual void mousePressEvent(QMouseEvent *e);
    void shoot(); //各類子彈射擊
    void product_mons(); //產生怪物
    void life(); //控管生命
    void Scheat(); //補血
    void follow(); //跟著時間跑
    void Srotate(); //子彈旋轉
    void saberdie();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *player, *end;
    QTimer *timer, *diee;
    QTime *through;
};

#endif // MAINWINDOW_H














