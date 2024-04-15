#include "double_mode.h"
#include "window.h"
#include <vector>
#include "victory_end.h"
#include "lose_end.h"
#include "end_double_mode.h"
#include "pause.h"
#include "ui_double_mode.h"
#include <QTimer>
#include <QTime>
#include <QPainter>
#include <QKeyEvent>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include "end1.h"
#include "end2.h"


double_mode::double_mode(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::double_mode)
{
    this->setObjectName("double_mode");
    this->setStyleSheet("#double_mode{border-image:url(:/resources/castle.jpg);}");
    ui->setupUi(this);
    hint_time = 0;
    hint_ending = 0;

    ui->lcdNumber->setDigitCount(3);
    ui->lcdNumber->setDecMode();
    ui->lcdNumber_2->setDigitCount(3);
    ui->lcdNumber_2->setDecMode();
    ui->lcdNumber_3->setDigitCount(3);
    ui->lcdNumber_3->setDecMode();
    ui->lcdNumber_4->setDigitCount(3);
    ui->lcdNumber_4->setDecMode();

    connect(_1stimer,SIGNAL(timeout()),this,SLOT(timedecrease()));//倒计时的槽函数
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&double_mode::repaint));//实时更新画面
    connect(timer, SIGNAL(timeout()), this, SLOT(showthing()));
    connect(timer, SIGNAL(timeout()), this, SLOT(hint()));
    timer->start(20);
    _1stimer->start(1000);
    pause_flag = 1;
    ui->pushButton->setText("pause");
    qsrand(QTime::currentTime().msec());
    int s=0;
        for(int i=0;i<length1+2;i++){
            for(int j=0;j<length1+2;j++){
                if(i==0||j==0||i==length1+1||j==length1+1){
                    block[s].x=j;
                    block[s].y=i;
                    block[s].lscore=0;//将block地图四周的空边生成
                }
                else{
                    block[s].x=j;
                    block[s].y=i;
                    block[s].lscore=qrand()%9+1;//随机生成block的地图
                }
                s++;
            }
        }
        for(int i=0;i<6;i++){
            bool flag=true;
            int a=qrand()%length1+1;
            int b=qrand()%length1+1;
            if(detect(a,b)->lscore==0){
                flag=false;
            }
            if(detect(a,b)->lscore>100&&detect(a,b)->lscore<110){
                flag=false;
            }
            if(!flag){
                i--;
            }
            else{
                detect(a,b)->lscore=i+100;
            }//分配道具位置
        }
        for(int i=0;i<length1+2;i++){
            for(int j=0;j<length1+2;j++){
                if(detect(i,j)->lscore==103){
                    int k=qrand()%9+1;
                    detect(i,j)->lscore=k;
                }
            }
        }
        if(length1<6){
            for(int i=0;i<length1+2;i++){
                for(int j=0;j<length1+2;j++){
                    if(detect(i,j)->lscore==102){
                        int k=qrand()%9+1;
                        detect(i,j)->lscore=k;
                    }
                }
            }
        }//判断特殊情况
        player1_x=0;
        player1_y=0;
        player2_x=length1+1;
        player2_y=0;
        Dead();
}

point1* double_mode::detect(int a,int b){
    for(int i=0;i<(length1+2)*(length1+2);i++){
        if(block[i].x==a&&block[i].y==b){
            return &block[i];
        }//辅助函数判断
    }
}

void double_mode::timedecrease(){
    if(timee1 <= 0&&timee2 <=0)//两人都倒计时结束
    {
        _1stimer->stop();
        if(score1>=score2){
            end1 *st=new end1;
            st->show();
            this->hide();
        }
        else{
            end2 *st=new end2;
            st->show();
            this->hide();
        }
    }
    if(timee1==0){
        player2_freezing=true;
    }
    if(timee2==0){
        player1_freezing=true;
    }
    if(timee1>0){timee1--;}
    if(timee2>0){timee2--;}
}

void double_mode::showthing()
{
    ui->lcdNumber->display(score1);
    ui->lcdNumber_2->display(score2);
    ui->lcdNumber_3->display(timee1);
    ui->lcdNumber_4->display(timee2);
}


void double_mode::endGame()
{
    timer->stop();
    end_double_mode *st=new end_double_mode;
    st->show();
    this->hide();
}

double_mode::~double_mode()
{
    delete ui;
}

void double_mode::delay(int time)
{
    QEventLoop loop;//定义一个循环线程
    QTimer::singleShot(time, &loop, SLOT(quit()));
    loop.exec();
}

void double_mode::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    for(int i=0;i<(length1+2)*(length1+2);i++){
            int x = 100*block[i].x+360;
            int y = 100*block[i].y+100;
            QPixmap icon;
            if(block[i].lscore!=0){
                if(block[i].lscore==1){
                   icon.load(":/resources/ball1.png");
                }
                if(block[i].lscore==2){
                   icon.load(":/resources/ball2.png");
                }
                if(block[i].lscore==3){
                   icon.load(":/resources/ball3.png");
                }
                if(block[i].lscore==4){
                   icon.load(":/resources/ball4.png");
                }
                if(block[i].lscore==5){
                   icon.load(":/resources/ball5.png");
                }
                if(block[i].lscore==6){
                   icon.load(":/resources/ball6.png");
                }
                if(block[i].lscore==7){
                   icon.load(":/resources/ball7.png");
                }
                if(block[i].lscore==8){
                   icon.load(":/resources/ball8.png");
                }
                if(block[i].lscore==9){
                   icon.load(":/resources/ball9.png");
                }
                if(block[i].lscore==11){
                   icon.load(":/resources/ball1_1.png");
                }
                if(block[i].lscore==12){
                   icon.load(":/resources/ball2_1.png");
                }
                if(block[i].lscore==13){
                   icon.load(":/resources/ball3_1.png");
                }
                if(block[i].lscore==14){
                   icon.load(":/resources/ball4_1.png");
                }
                if(block[i].lscore==15){
                   icon.load(":/resources/ball5_1.png");
                }
                if(block[i].lscore==16){
                   icon.load(":/resources/ball6_1.png");
                }
                if(block[i].lscore==17){
                   icon.load(":/resources/ball7_1.png");
                }
                if(block[i].lscore==18){
                   icon.load(":/resources/ball8_1.png");
                }
                if(block[i].lscore==19){
                   icon.load(":/resources/ball9_1.png");
                }
                if(block[i].lscore==21){
                    icon.load(":/resources/ball1_2.png");
                 }
                if(block[i].lscore==22){
                   icon.load(":/resources/ball2_2.png");
                }
                if(block[i].lscore==23){
                   icon.load(":/resources/ball3_2.png");
                }
                if(block[i].lscore==24){
                   icon.load(":/resources/ball4_2.png");
                }
                if(block[i].lscore==25){
                   icon.load(":/resources/ball5_2.png");
                }
                if(block[i].lscore==26){
                   icon.load(":/resources/ball6_2.png");
                }
                if(block[i].lscore==27){
                   icon.load(":/resources/ball7_2.png");
                }
                if(block[i].lscore==28){
                   icon.load(":/resources/ball8_2.png");
                }
                if(block[i].lscore==29){
                   icon.load(":/resources/ball9_2.png");
                }
                if(block[i].lscore==31){
                    icon.load(":/resources/ball1_3.png");
                 }
                if(block[i].lscore==32){
                   icon.load(":/resources/ball2_3.png");
                }
                if(block[i].lscore==33){
                   icon.load(":/resources/ball3_3.png");
                }
                if(block[i].lscore==34){
                   icon.load(":/resources/ball4_3.png");
                }
                if(block[i].lscore==35){
                   icon.load(":/resources/ball5_3.png");
                }
                if(block[i].lscore==36){
                   icon.load(":/resources/ball6_3.png");
                }
                if(block[i].lscore==37){
                   icon.load(":/resources/ball7_3.png");
                }
                if(block[i].lscore==38){
                   icon.load(":/resources/ball8_3.png");
                }
                if(block[i].lscore==39){
                   icon.load(":/resources/ball9_3.png");
                }
                if(block[i].lscore==1000){
                   icon.load(":/resources/N_S.png");
                }
                if(block[i].lscore==1001){
                   icon.load(":/resources/W_E.png");
                }
                if(block[i].lscore==1002){
                   icon.load(":/resources/S_E.png");
                }
                if(block[i].lscore==1003){
                   icon.load(":/resources/N_E.png");
                }
                if(block[i].lscore==1004){
                   icon.load(":/resources/W_N.png");
                }
                if(block[i].lscore==1005){
                   icon.load(":/resources/W_S.png");
                }
                if(block[i].lscore==100){
                   icon.load(":/resources/shuffle.png");
                }
                if(block[i].lscore==101){
                   icon.load(":/resources/plus.png");
                }
                if(block[i].lscore==102){
                   icon.load(":/resources/hint.png");
                }
                if(block[i].lscore==103){
                   icon.load(":/resources/flash.png");
                }
                if(block[i].lscore==104){
                   icon.load(":/resources/freeze.png");
                }
                if(block[i].lscore==105){
                   icon.load(":/resources/dizzy.png");
                }
            painter.drawPixmap(x,y,100,100,icon);
        }
    }
    int a=370+100*player1_x;
    int b=100+100*player1_y;
    int c=370+100*player2_x;
    int d=100+100*player2_y;
    player1_1.load(":/resources/user1.png");
    player2_2.load(":/resources/user2.png");
    painter.drawPixmap(a,b,80,80,player1_1);
    painter.drawPixmap(c,d,80,80,player2_2);
    painter.end();
}

void double_mode::keyPressEvent(QKeyEvent *event)
{
    if (pause_flag){
        if(!player1_freezing){
            keyPressEvent1(event);
        }
        if(!player2_freezing){
            keyPressEvent2(event);
        }
    }
}

void double_mode::keyPressEvent1(QKeyEvent *event){
    if(!player1_dizzy){
        if(Qt::Key_A==event->key()){
            left_chooseBlock1();
            player1_x-=1;
        }
        if(Qt::Key_D==event->key()){
            right_chooseBlock1();
            player1_x+=1;
        }
        if(Qt::Key_W==event->key()){
            up_chooseBlock1();
            player1_y-=1;
        }
        if(Qt::Key_S==event->key()){
            down_chooseBlock1();
            player1_y+=1;
        }
    }
    else{
        if(Qt::Key_A==event->key()){
            right_chooseBlock1();
            player1_x+=1;
        }
        if(Qt::Key_D==event->key()){
            left_chooseBlock1();
            player1_x-=1;
        }
        if(Qt::Key_W==event->key()){
            down_chooseBlock1();
            player1_y+=1;
        }
        if(Qt::Key_S==event->key()){
            up_chooseBlock1();
            player1_y-=1;
        }

    }
}

void double_mode::keyPressEvent2(QKeyEvent *event){
    if(!player2_dizzy){
        if(Qt::Key_J==event->key()){
            left_chooseBlock2();
            player2_x-=1;
        }
        if(Qt::Key_L==event->key()){
            right_chooseBlock2();
            player2_x+=1;
        }
        if(Qt::Key_I==event->key()){
            up_chooseBlock2();
            player2_y-=1;
        }
        if(Qt::Key_K==event->key()){
            down_chooseBlock2();
            player2_y+=1;
        }
    }
    else{
        if(Qt::Key_J==event->key()){
            right_chooseBlock2();
            player2_x+=1;
        }
        if(Qt::Key_L==event->key()){
            left_chooseBlock2();
            player2_x-=1;
        }
        if(Qt::Key_I==event->key()){
            down_chooseBlock2();
            player2_y+=1;
        }
        if(Qt::Key_K==event->key()){
            up_chooseBlock2();
            player2_y-=1;
        }
    }
}

void double_mode::eliminate(int ax, int ay, int bx, int by)
{
    detect(ax,ay)->lscore = 0;
    detect(bx,by)->lscore = 0;
    Dead();
}


void double_mode::left_chooseBlock1(){
    if(player1_x<=0) {player1_x+=1;}
    int i = player1_x;
    int j = player1_y;
    if (player1_x>=0 && player1_x <= length1+1 && player1_y>=0 &&player1_y <= length1+1)//判断是否出地图范围
        if (detect(i,j)->lscore>=100&&detect(i,j)->lscore<110){
            int tool=detect(i,j)->lscore;
            detect(i,j)->lscore = 0;
            tool_s(tool,1);//tool
        }
    int a = -1 ,b = -1;
    a = i-1;
    b = j;
    if (a >= 1 && a <= length1 && b >= 1 && b <= length1){
        if((detect(a,b)->lscore>0&&detect(a,b)->lscore<100)){
        player1_x+=1;}
        if((detect(a,b)->lscore>0&&detect(a,b)->lscore<10)||(detect(a,b)->lscore>20&&detect(a,b)->lscore<30)){
            detect(a,b)->lscore=(detect(a,b)->lscore)%10+10;
            if(!single1){//未选过block的情况
                single1=true;
                former1_x=a;
                former1_y=b;
            }
            else{
                if(whetherlink(former1_x,former1_y,a,b)){
                    link(former1_x,former1_y,a,b);
                    score1+=(detect(a,b)->lscore)%10;
                    eliminate(former1_x,former1_y,a,b);
                    Dead();
                }
                else{
                    detect(former1_x,former1_y)->lscore=(detect(former1_x,former1_y)->lscore)%10;
                    detect(a,b)->lscore%=10;
                    if(hint1_x!=-1){
                        if(detect(hint1_x,hint1_y)->lscore>0&&detect(hint1_x,hint1_y)->lscore<10){
                            detect(hint1_x,hint1_y)->lscore+=20;//避免hint的block被消除
                        }
                        if(detect(hint2_x,hint2_y)->lscore>0&&detect(hint2_x,hint2_y)->lscore<10){
                            detect(hint2_x,hint2_y)->lscore+=20;
                        }
                    }
                }
                single1=false;
            }
        }
    }
}

void double_mode::right_chooseBlock1(){
    if(player1_x >= length1+1){player1_x-=1;}
    int i = player1_x;
    int j = player1_y;
    if (player1_x>=0 && player1_x <= length1+1 && player1_y>=0 &&player1_y <= length1+1)
        if (detect(i,j)->lscore>=100&&detect(i,j)->lscore<110){
            int tool=detect(i,j)->lscore;
            detect(i,j)->lscore = 0;
            tool_s(tool,1);
        }
    int a = -1 ,b = -1;
        a = i+1;
        b = j;
    if (a >= 1 && a <= length1 && b >= 1 && b <= length1){
        if((detect(a,b)->lscore>0&&detect(a,b)->lscore<100)){
        player1_x-=1;}
        if((detect(a,b)->lscore>0&&detect(a,b)->lscore<10)||(detect(a,b)->lscore>20&&detect(a,b)->lscore<30)){
            detect(a,b)->lscore=(detect(a,b)->lscore)%10+10;
            if(!single1){
                single1=true;
                former1_x=a;
                former1_y=b;
            }
            else{
                if(whetherlink(former1_x,former1_y,a,b)){
                    link(former1_x,former1_y,a,b);
                    score1+=detect(a,b)->lscore%10;
                    eliminate(former1_x,former1_y,a,b);
                    Dead();
                }
                else{
                    detect(former1_x,former1_y)->lscore=detect(former1_x,former1_y)->lscore%10;
                    detect(a,b)->lscore%=10;
                    if(hint1_x!=-1){
                        if(detect(hint1_x,hint1_y)->lscore>0&&detect(hint1_x,hint1_y)->lscore<10){
                            detect(hint1_x,hint1_y)->lscore+=20;
                        }
                        if(detect(hint2_x,hint2_y)->lscore>0&&detect(hint2_x,hint2_y)->lscore<10){
                            detect(hint2_x,hint2_y)->lscore+=20;
                        }
                    }
                }
                single1=false;
            }
        }
    }
}

void double_mode::up_chooseBlock1(){
    if(player1_y<=0){player1_y+=1;}
    int i = player1_x;
    int j=  player1_y;
    if (player1_x>=0 && player1_x <= length1+1 && player1_y>=0 &&player1_y <= length1+1)
        if (detect(i,j)->lscore>=100&&detect(i,j)->lscore<110){
            int tool=detect(i,j)->lscore;
            detect(i,j)->lscore = 0;
            tool_s(tool,1);
        }
    int a=-1,b=-1;
    a=i;
    b=j-1;
    if (a >= 1 && a <= length1 && b >= 1 && b <= length1){
        if((detect(a,b)->lscore>0&&detect(a,b)->lscore<100)){
        player1_y+=1;}
        if((detect(a,b)->lscore>0&&detect(a,b)->lscore<10)||(detect(a,b)->lscore>20&&detect(a,b)->lscore<30)){
            detect(a,b)->lscore=(detect(a,b)->lscore)%10+10;
            if(!single1){
                single1=true;
                former1_x=a;
                former1_y=b;
            }
            else{
                if(whetherlink(former1_x,former1_y,a,b)){
                    link(former1_x,former1_y,a,b);
                    score1+=detect(a,b)->lscore%10;
                    eliminate(former1_x,former1_y,a,b);
                    Dead();
                }
                else{
                    detect(former1_x,former1_y)->lscore=detect(former1_x,former1_y)->lscore%10;
                    detect(a,b)->lscore%=10;
                    if(hint1_x!=-1){
                        if(detect(hint1_x,hint1_y)->lscore>0&&detect(hint1_x,hint1_y)->lscore<10){
                            detect(hint1_x,hint1_y)->lscore+=20;
                        }
                        if(detect(hint2_x,hint2_y)->lscore>0&&detect(hint2_x,hint2_y)->lscore<10){
                            detect(hint2_x,hint2_y)->lscore+=20;
                        }
                    }
                }
            single1=false;
        }
    }
    }
}

void double_mode::down_chooseBlock1(){
    if(player1_y>=length1+1){player1_y-=1;}
    int i = player1_x;
    int j=  player1_y;
    if (player1_x>=0 && player1_x <= length1+1 && player1_y>=0 &&player1_y <= length1+1)
        if (detect(i,j)->lscore>=100&&detect(i,j)->lscore<110){
            int tool=detect(i,j)->lscore;
            detect(i,j)->lscore = 0;
            tool_s(tool,1);
        }
    int a = -1 ,b = -1;
        a = i;
        b = j+1;
    if (a >= 1 && a <= length1 && b >= 1 && b <= length1){
        if(detect(a,b)->lscore>0&&detect(a,b)->lscore<100){
            player1_y-=1;
        }
        if((detect(a,b)->lscore>0&&detect(a,b)->lscore<10)||(detect(a,b)->lscore>20&&detect(a,b)->lscore<30)){
            detect(a,b)->lscore=(detect(a,b)->lscore)%10+10;
            if(!single1){
                single1=true;
                former1_x=a;
                former1_y=b;
            }
            else{
                if(whetherlink(former1_x,former1_y,a,b)){
                    link(former1_x,former1_y,a,b);
                    score1+=detect(a,b)->lscore%10;
                    eliminate(former1_x,former1_y,a,b);
                    Dead();
                }
                else{
                    detect(former1_x,former1_y)->lscore=detect(former1_x,former1_y)->lscore%10;
                    detect(a,b)->lscore%=10;
                    if(hint1_x!=-1){
                        if(detect(hint1_x,hint1_y)->lscore>0&&detect(hint1_x,hint1_y)->lscore<10){
                            detect(hint1_x,hint1_y)->lscore+=20;
                        }
                        if(detect(hint2_x,hint2_y)->lscore>0&&detect(hint2_x,hint2_y)->lscore<10){
                            detect(hint2_x,hint2_y)->lscore+=20;
                        }
                    }
                }
                single1=false;
            }
        }
    }
}

void double_mode::left_chooseBlock2(){
    if(player2_x<=0) {player2_x+=1;}
    int i = player2_x;
    int j = player2_y;
    if (player2_x>=0 && player2_x <= length1+1 && player2_y>=0 &&player2_y <= length1+1)
        if (detect(i,j)->lscore>=100&&detect(i,j)->lscore<110){
            int tool=detect(i,j)->lscore;
            detect(i,j)->lscore = 0;
            tool_s(tool,2);
        }
    int a = -1 ,b = -1;
    a = i-1;
    b = j;
    if (a >= 1 && a <= length1 && b >= 1 && b <= length1){
        if((detect(a,b)->lscore>0&&detect(a,b)->lscore<100)){
        player2_x+=1;}
        if((detect(a,b)->lscore>0&&detect(a,b)->lscore<10)||(detect(a,b)->lscore>20&&detect(a,b)->lscore<30)){
            detect(a,b)->lscore=(detect(a,b)->lscore)%10+30;
            if(!single2){
                single2=true;
                former2_x=a;
                former2_y=b;
            }
            else{
                if(whetherlink(former2_x,former2_y,a,b)){
                    link(former2_x,former2_y,a,b);
                    score2+=(detect(a,b)->lscore)%10;
                    eliminate(former2_x,former2_y,a,b);
                    Dead();
                }
                else{
                    detect(former2_x,former2_y)->lscore=(detect(former2_x,former2_y)->lscore)%10;
                    detect(a,b)->lscore%=10;
                    if(hint1_x!=-1){
                        if(detect(hint1_x,hint1_y)->lscore>0&&detect(hint1_x,hint1_y)->lscore<10){
                            detect(hint1_x,hint1_y)->lscore+=20;
                        }
                        if(detect(hint2_x,hint2_y)->lscore>0&&detect(hint2_x,hint2_y)->lscore<10){
                            detect(hint2_x,hint2_y)->lscore+=20;
                        }
                    }
                }
                single2=false;
            }
        }
    }
}

void double_mode::right_chooseBlock2(){
    if(player2_x >= length1+1){player2_x-=1;}
    int i = player2_x;
    int j = player2_y;
    if (player2_x>=0 && player2_x <= length1+1 && player2_y>=0 &&player2_y <= length1+1)
        if (detect(i,j)->lscore>=100&&detect(i,j)->lscore<110){
            int tool=detect(i,j)->lscore;
            detect(i,j)->lscore = 0;
            tool_s(tool,2);
        }
    int a = -1 ,b = -1;
        a = i+1;
        b = j;
    if (a >= 1 && a <= length1 && b >= 1 && b <= length1){
        if((detect(a,b)->lscore>0&&detect(a,b)->lscore<100)){
        player2_x-=1;}
        if((detect(a,b)->lscore>0&&detect(a,b)->lscore<10)||(detect(a,b)->lscore>20&&detect(a,b)->lscore<30)){
            detect(a,b)->lscore=(detect(a,b)->lscore)%10+30;
            if(!single2){
                single2=true;
                former2_x=a;
                former2_y=b;
            }
            else{
                if(whetherlink(former2_x,former2_y,a,b)){
                    link(former2_x,former2_y,a,b);
                    score2+=detect(a,b)->lscore%10;
                    eliminate(former2_x,former2_y,a,b);
                    Dead();
                }
                else{
                    detect(former2_x,former2_y)->lscore=detect(former2_x,former2_y)->lscore%10;
                    detect(a,b)->lscore%=10;
                    if(hint1_x!=-1){
                        if(detect(hint1_x,hint1_y)->lscore>0&&detect(hint1_x,hint1_y)->lscore<10){
                            detect(hint1_x,hint1_y)->lscore+=20;
                        }
                        if(detect(hint2_x,hint2_y)->lscore>0&&detect(hint2_x,hint2_y)->lscore<10){
                            detect(hint2_x,hint2_y)->lscore+=20;
                        }
                    }
                }
                single2=false;
            }
        }
    }
}

void double_mode::up_chooseBlock2(){
    if(player2_y<=0){player2_y+=1;}
    int i = player2_x;
    int j=  player2_y;
    if (player2_x>=0 && player2_x <= length1+1 && player2_y>=0 &&player2_y <= length1+1)
        if (detect(i,j)->lscore>=100&&detect(i,j)->lscore<110){
            int tool=detect(i,j)->lscore;
            detect(i,j)->lscore = 0;
            tool_s(tool,2);
        }
    int a=-1,b=-1;
    a=i;
    b=j-1;
    if (a >= 1 && a <= length1 && b >= 1 && b <= length1){
        if((detect(a,b)->lscore>0&&detect(a,b)->lscore<100)){
        player2_y+=1;}
        if((detect(a,b)->lscore>0&&detect(a,b)->lscore<10)||(detect(a,b)->lscore>20&&detect(a,b)->lscore<30)){
            detect(a,b)->lscore=(detect(a,b)->lscore)%10+30;
            if(!single2){
                single2=true;
                former2_x=a;
                former2_y=b;
            }
            else{
                if(whetherlink(former2_x,former2_y,a,b)){
                    link(former2_x,former2_y,a,b);
                    score2+=detect(a,b)->lscore%10;
                    eliminate(former2_x,former2_y,a,b);
                    Dead();
                }
                else{
                    detect(former2_x,former2_y)->lscore=detect(former2_x,former2_y)->lscore%10;
                    detect(a,b)->lscore%=10;
                    if(hint1_x!=-1){
                        if(detect(hint1_x,hint1_y)->lscore>0&&detect(hint1_x,hint1_y)->lscore<10){
                            detect(hint1_x,hint1_y)->lscore+=20;
                        }
                        if(detect(hint2_x,hint2_y)->lscore>0&&detect(hint2_x,hint2_y)->lscore<10){
                            detect(hint2_x,hint2_y)->lscore+=20;
                        }
                    }
                }
            single2=false;
        }
    }
    }
}

void double_mode::down_chooseBlock2(){
    if(player2_y>=length1+1){player2_y-=1;}
    int i = player2_x;
    int j=  player2_y;
    if (player2_x>=0 && player2_x <= length1+1 && player2_y>=0 &&player2_y <= length1+1)
        if (detect(i,j)->lscore>=100&&detect(i,j)->lscore<110){
            int tool=detect(i,j)->lscore;
            detect(i,j)->lscore = 0;
            tool_s(tool,2);
        }
    int a = -1 ,b = -1;
        a = i;
        b = j+1;
    if (a >= 1 && a <= length1 && b >= 1 && b <= length1){
        if(detect(a,b)->lscore>0&&detect(a,b)->lscore<100){
            player2_y-=1;
        }
        if((detect(a,b)->lscore>0&&detect(a,b)->lscore<10)||(detect(a,b)->lscore>20&&detect(a,b)->lscore<30)){
            detect(a,b)->lscore=(detect(a,b)->lscore)%10+30;
            if(!single2){
                single2=true;
                former2_x=a;
                former2_y=b;
            }
            else{
                if(whetherlink(former2_x,former2_y,a,b)){
                    link(former2_x,former2_y,a,b);
                    score2+=detect(a,b)->lscore%10;
                    eliminate(former2_x,former2_y,a,b);
                    Dead();
                }
                else{
                    detect(former2_x,former2_y)->lscore=detect(former2_x,former2_y)->lscore%10;
                    detect(a,b)->lscore%=10;
                    if(hint1_x!=-1){
                        if(detect(hint1_x,hint1_y)->lscore>0&&detect(hint1_x,hint1_y)->lscore<10){
                            detect(hint1_x,hint1_y)->lscore+=20;
                        }
                        if(detect(hint2_x,hint2_y)->lscore>0&&detect(hint2_x,hint2_y)->lscore<10){
                            detect(hint2_x,hint2_y)->lscore+=20;
                        }
                    }
                }
                single2=false;
            }
        }
    }
}


void double_mode::tool_s(int tool,int member){
      if(tool==101){
        plus(member);
      }
      if(tool==100){
        shuffle();
      }
      if(tool==102){
        hint_time = 1;
        hint_ending = 1;
        QTimer::singleShot(20000,this,SLOT(dehint()));
      }
      if(tool==103){
        /*if(member==1){
            player1_flash=1;
        }
        if(member==2){
            player2_flash=1;
        }
        QTimer::singleShot(10000,this,SLOT(deflash()));
        break;*/}
       if(tool==104){
        freeze(member);
        QTimer::singleShot(10000,this,SLOT(defreeze()));
       }
       if(tool==105){
        dizzy(member);
        QTimer::singleShot(10000,this,SLOT(dedizzy()));
       }
       Dead();
}



void double_mode::deflash(){
    if(player1_flash==1){
        player1_flash=0;
    }
    if(player2_flash==1){
        player2_flash=0;
    }
}

bool double_mode::straightwhetherlink(int ax, int ay, int bx, int by)
{
    if (((detect(ax,ay)->lscore%10) != (detect(bx,by)->lscore%10))//两端block不同
            &&(!(detect(ax,ay)->lscore!=0&&detect(bx,by)->lscore==0))//一端为空
            &&(!(detect(ax,ay)->lscore==0&&detect(bx,by)->lscore==0))
            &&(!(detect(ax,ay)->lscore==0&&detect(bx,by)->lscore))){
        return false;
    }
    else{

        if (ax==bx&&ay==by)
            return true;
        else{
            if (ax==bx&&ay<by){
                bool flag=true;
                for(int i=ay+1;i<by;i++){
                    if(detect(ax,i)->lscore!=0)
                    {flag=false;}
                }
                return flag;
            }
            else{
                if(ax==bx&&ay>by){
                    bool flag=true;
                    for(int i=by+1;i<ay;i++){
                        if(detect(ax,i)->lscore!=0){
                            flag=false;
                        }
                    }
                    return flag;
                }
            }
            if(ay==by&&ax<bx){
                bool flag=true;
                for(int i=ax+1;i<bx;i++){
                    if(detect(i,ay)->lscore!=0){
                        flag=false;
                    }
                }
                return flag;
            }
            else{
                if(ay==by&&ax>bx){
                    bool flag=true;
                    for(int i=bx+1;i<ax;i++){
                        if(detect(i,ay)->lscore!=0){
                            flag=false;
                        }
                    }
                    return flag;
                }
            }
                return false;
        }
    }
}


bool double_mode::whetherlink(int ax,int ay,int bx,int by){
    if((detect(ax,ay)->lscore%10)!=(detect(bx,by)->lscore%10)){
        return false;
    }
    for(int i=0;i<length1+2;i++){//折成最多三段直线相连
        if(straightwhetherlink(ax,ay,i,ay)&&straightwhetherlink(i,ay,i,by)
                &&straightwhetherlink(bx,by,i,by)){
            return true;
        }
    }
    for(int i=0;i<length1+2;i++){
        if(straightwhetherlink(ax,ay,i,ay)&&straightwhetherlink(i,ay,i,by)
                &&straightwhetherlink(i,by,bx,by)){
            return true;
        }
    }
    for(int i=0;i<length1+2;i++){
        if(straightwhetherlink(ax,ay,ax,i)&&straightwhetherlink(ax,i,bx,i)
                &&straightwhetherlink(bx,i,bx,by)){
            return true;
        }
    }
    for(int i=0;i<length1+2;i++){
        if(straightwhetherlink(ax,ay,ax,i)&&straightwhetherlink(ax,i,bx,i)
                &&straightwhetherlink(bx,i,bx,by)){
            return true;
        }
    }
    return false;
}

void double_mode::straightlink(int ax, int ay, int bx, int by){
     if(ax==bx){
         if(ay>by){
             for(int i=by+1;i<ay;i++){
                 detect(ax,i)->lscore=1000;
             }
         }
         if(by>ay){
             for(int i=ay+1;i<by;i++){
                 detect(ax,i)->lscore=1000;
             }
         }
     }
     if(ay==by){
         if(ax>bx){
             for(int i=bx+1;i<ax;i++){
                 detect(i,ay)->lscore=1001;
             }
         }
         if(bx>ax){
             for(int i=ax+1;i<bx;i++){
                 detect(i,ay)->lscore=1001;
             }
         }
     }
     delay(100);
     de_straightlink(ax,ay,bx,by);
}


void double_mode::de_straightlink(int ax, int ay, int bx, int by){
    if(ax==bx){
        if(ay>by){
            for(int i=by+1;i<ay;i++){
                detect(ax,i)->lscore=0;
            }
        }
        if(by>ay){
            for(int i=ay+1;i<by;i++){
                detect(ax,i)->lscore=0;
            }
        }
    }
    if(ay==by){
        if(ax>bx){
            for(int i=bx+1;i<ax;i++){
                detect(i,ay)->lscore=0;
            }
        }
        if(bx>ax){
            for(int i=ax+1;i<bx;i++){
                detect(i,ay)->lscore=0;
            }
        }
    }
}

void double_mode::link(int ax, int ay, int bx, int by){
    if((ax==bx||ay==by)&&straightwhetherlink(ax,ay,bx,by)){
        straightlink(ax,ay,bx,by);//直接相连
    }
    else{
        if(ax<bx){
            if(ay>by){//一次拐角
                if(straightwhetherlink(ax,ay,ax,by)&&straightwhetherlink(ax,by,bx,by)){
                    straightlink(ax,ay,ax,by);
                    straightlink(ax,by,bx,by);
                    detect(ax,by)->lscore=1002;
                    delay(100);
                    detect(ax,by)->lscore=0;
                    return;
                }
                if(straightwhetherlink(ax,ay,bx,ay)&&straightwhetherlink(bx,ay,bx,by)){
                    straightlink(ax,ay,bx,ay);
                    straightlink(bx,ay,bx,by);
                    detect(bx,ay)->lscore=1004;
                    delay(100);
                    detect(bx,ay)->lscore=0;
                    return;
                }
            }
            else{
                   if(straightwhetherlink(ax,ay,ax,by)&&straightwhetherlink(ax,by,bx,by)){
                       straightlink(ax,ay,ax,by);
                       straightlink(ax,by,bx,by);
                       detect(ax,by)->lscore=1003;
                       delay(100);
                       detect(ax,by)->lscore=0;
                       return;
                   }
                   if(straightwhetherlink(ax,ay,bx,ay)&&straightwhetherlink(bx,ay,bx,by)){
                       straightlink(ax,ay,bx,ay);
                       straightlink(bx,ay,bx,by);
                       detect(bx,ay)->lscore=1005;
                       delay(100);
                       detect(bx,ay)->lscore=0;
                       return;
                }
            }
        }
        if(ax>bx){
            if(ay>by){
                if(straightwhetherlink(ax,ay,bx,ay)&&straightwhetherlink(bx,ay,bx,by)){
                    straightlink(ax,ay,bx,ay);
                    straightlink(bx,ay,bx,by);
                    detect(bx,ay)->lscore=1003;
                    delay(100);
                    detect(bx,ay)->lscore=0;
                    return;
                }
                if(straightwhetherlink(ax,ay,ax,by)&&straightwhetherlink(ax,by,bx,by)){
                    straightlink(ax,ay,ax,by);
                    straightlink(ax,by,bx,by);
                    detect(ax,by)->lscore=1005;
                    delay(100);
                    detect(ax,by)->lscore=0;
                    return;
                }
            }
            else{
                if(straightwhetherlink(ax,ay,bx,ay)&&straightwhetherlink(bx,ay,bx,by)){
                    straightlink(ax,ay,bx,ay);
                    straightlink(bx,ay,bx,by);
                    detect(bx,ay)->lscore=1003;
                    delay(100);
                    detect(bx,ay)->lscore=0;
                    return;
                }
                if(straightwhetherlink(ax,ay,ax,by)&&straightwhetherlink(ax,by,bx,by)){
                    straightlink(ax,ay,ax,by);
                    straightlink(ax,by,bx,by);
                    detect(ax,by)->lscore=1004;
                    delay(100);
                    detect(ax,by)->lscore=0;
                    return;
                }
            }
        }//两次拐角
            for(int i=0;i<length1+2;i++){
                if(ax==i||bx==i){
                    continue;
                }
                if(ax>bx){
                    std::swap(ax,bx);
                    std::swap(ay,by);
                }
                if(ay>by){
                    if(straightwhetherlink(ax,ay,i,ay)&&straightwhetherlink(i,ay,i,by)&&straightwhetherlink(i,by,bx,by))
                    {
                        if(i<ax){
                            straightlink(i,ay,ax,ay);
                            straightlink(i,ay,i,by);
                            straightlink(i,by,bx,by);
                            detect(i,ay)->lscore=1003;
                            detect(i,by)->lscore=1002;
                            delay(100);
                            detect(i,ay)->lscore=0;
                            detect(i,by)->lscore=0;
                            return;
                        }
                        if(i>ax&&i<bx){
                            straightlink(i,ay,ax,ay);
                            straightlink(i,ay,i,by);
                            straightlink(i,by,bx,by);
                            detect(i,ay)->lscore=1004;
                            detect(i,by)->lscore=1002;
                            delay(100);
                            detect(i,ay)->lscore=0;
                            detect(i,by)->lscore=0;
                            return;
                        }
                        else{
                            straightlink(i,ay,ax,ay);
                            straightlink(i,ay,i,by);
                            straightlink(i,by,bx,by);
                            detect(i,ay)->lscore=1004;
                            detect(i,by)->lscore=1005;
                            delay(100);
                            detect(i,ay)->lscore=0;
                            detect(i,by)->lscore=0;
                            return;
                        }
                    }
                    if(straightwhetherlink(ax,ay,ax,i)&&straightwhetherlink(ax,i,bx,i)&&straightwhetherlink(bx,i,bx,by)){
                        if(i>ay){
                            straightlink(ax,ay,ax,i);
                            straightlink(ax,i,bx,i);
                            straightlink(bx,i,bx,by);
                            detect(ax,i)->lscore=1003;
                            detect(bx,i)->lscore=1004;
                            delay(100);
                            detect(ax,i)->lscore=0;
                            detect(bx,i)->lscore=0;
                            return;
                        }
                        if(i<ay&&i>by){
                            straightlink(ax,ay,ax,i);
                            straightlink(ax,i,bx,i);
                            straightlink(bx,i,bx,by);
                            detect(ax,i)->lscore=1003;
                            detect(bx,i)->lscore=1005;
                            delay(100);
                            detect(ax,i)->lscore=0;
                            detect(bx,i)->lscore=0;
                            return;
                        }
                        else{
                            straightlink(ax,ay,ax,i);
                            straightlink(ax,i,bx,i);
                            straightlink(bx,i,bx,by);
                            detect(ax,i)->lscore=1002;
                            detect(bx,i)->lscore=1005;
                            delay(100);
                            detect(ax,i)->lscore=0;
                            detect(bx,i)->lscore=0;
                            return;
                        }
                    }
                }
                else{
                    if(straightwhetherlink(ax,ay,i,ay)&&straightwhetherlink(i,ay,i,by)&&straightwhetherlink(i,by,bx,by))
                    {
                        if(i<ax){
                            straightlink(i,ay,ax,ay);
                            straightlink(i,ay,i,by);
                            straightlink(i,by,bx,by);
                            detect(i,ay)->lscore=1002;
                            detect(i,by)->lscore=1003;
                            delay(100);
                            detect(i,ay)->lscore=0;
                            detect(i,by)->lscore=0;
                            return;
                        }
                        if(i>ax&&i<bx){
                            straightlink(i,ay,ax,ay);
                            straightlink(i,ay,i,by);
                            straightlink(i,by,bx,by);
                            detect(i,ay)->lscore=1005;
                            detect(i,by)->lscore=1003;
                            delay(100);
                            detect(i,ay)->lscore=0;
                            detect(i,by)->lscore=0;
                            return;
                        }
                        else{
                            straightlink(i,ay,ax,ay);
                            straightlink(i,ay,i,by);
                            straightlink(i,by,bx,by);
                            detect(i,ay)->lscore=1005;
                            detect(i,by)->lscore=1004;
                            delay(100);
                            detect(i,ay)->lscore=0;
                            detect(i,by)->lscore=0;
                            return;
                        }
                    }
                    if(straightwhetherlink(ax,ay,ax,i)&&straightwhetherlink(ax,i,bx,i)&&straightwhetherlink(bx,i,bx,by)){
                        if(i>by){
                            straightlink(ax,ay,ax,i);
                            straightlink(ax,i,bx,i);
                            straightlink(bx,i,bx,by);
                            detect(ax,i)->lscore=1003;
                            detect(bx,i)->lscore=1004;
                            delay(100);
                            detect(ax,i)->lscore=0;
                            detect(bx,i)->lscore=0;
                            return;
                        }
                        if(i<by&&i>ay){
                            straightlink(ax,ay,ax,i);
                            straightlink(ax,i,bx,i);
                            straightlink(bx,i,bx,by);
                            detect(ax,i)->lscore=1003;
                            detect(bx,i)->lscore=1005;
                            delay(100);
                            detect(ax,i)->lscore=0;
                            detect(bx,i)->lscore=0;
                            return;
                        }
                        else{
                            straightlink(ax,ay,ax,i);
                            straightlink(ax,i,bx,i);
                            straightlink(bx,i,bx,by);
                            detect(ax,i)->lscore=1002;
                            detect(bx,i)->lscore=1005;
                            delay(100);
                            detect(ax,i)->lscore=0;
                            detect(bx,i)->lscore=0;
                            return;
                        }
                    }
                }
            }
       }
}

void double_mode::Dead()
{
    bool ifdead=false;
    for (int i=1; i<=length1; i++){
        for (int j=1; j<=length1; j++){
            if (detect(i,j)->lscore!=0){
                for (int k=i; k<=length1; k++){
                    for (int l=1; l<=length1; l++){
                        if (!(k==i&&l==j))//两点相同
                            if (whetherlink(i,j,k,l)){
                                ifdead=true;
                                break;
                            }
                    }if(ifdead) break;
                }if(ifdead) break;
            }
        }if(ifdead) break;
    }
    if (!ifdead){
        timer->stop();
        if(score1>=score2){
            end1 *st=new end1;
            st->show();
            this->hide();
        }
        else{
            end2 *st=new end2;
            st->show();
            this->hide();
        }
    }
}

bool double_mode::dead()
{
    bool ifdead=false;
    for (int i=1; i<=length1; i++){
        for (int j=1; j<=length1; j++){
            if (detect(i,j)->lscore!=0){
                for (int k=i; k<=length1; k++){
                    for (int l=1; l<=length1; l++){
                        if (!(k==i&&l==j))
                            if (whetherlink(i,j,k,l)){
                                ifdead=true;
                                break;
                            }
                    }
                }
            }
        }
    }
    return ifdead;
}

void double_mode::plus(int member)
{
    if(member==1){
        if (timee2>=totaltime1-30){
            timee2=totaltime1;
        }
        else{
            timee2+=30;
        }
    }
    if(member==2){
         if (timee1>=totaltime1-30){
             timee1=totaltime1;
        }
         else{
             timee1+=30;
        }
    }
}

void double_mode::shuffle(){
    single1=false;
    single2=false;
    std::vector<int> a;
    for(int i=1;i<=length1;i++){
        for(int j=1;j<=length1;j++){
                if(!(detect(i,j)->lscore>=100&&detect(i,j)->lscore<110)){
                    a.push_back(detect(i,j)->lscore%10);
                    detect(i,j)->lscore=0;
                }
                else{
                   a.push_back(detect(i,j)->lscore);
                   detect(i,j)->lscore=0;
                }
            }
    }
    qsrand(QTime::currentTime().msec());
    for(int w=0;w<int(a.size());w++){
        int z=qrand()%(length1)+1;
        int x=qrand()%(length1)+1;
        bool flag=true;
        if(detect(z,x)->lscore!=0){
            flag=false;//已分配跳过
        }
        if(detect(z,x)->lscore>100&&detect(z,x)->lscore<110){
            flag=false;
        }
        if(!flag){w--;}
        else{
                detect(z,x)->lscore=a[w];//随机重新分配已有的block
        }
    }
    hint1_x=-1;
    hint1_y=-1;
    hint2_x=-1;
    hint2_y=-1;
    player1_x=0;
    player1_y=0;
    player2_x=length1+1;
    player2_y=0;
}

void double_mode::hint()
{
    if(hint_time==1){
        int k=0;int p=0;
        if(hint1_x!=-1){
        if(detect(hint1_x,hint1_y)->lscore!=0){
            k++;
        }
        if(detect(hint2_x,hint2_y)->lscore!=0){
            k++;
        }
        for(int i=1;i<=length1;i++){
            for(int j=1;j<=length1;j++){
                if(detect(i,j)->lscore>10&&detect(i,j)->lscore<20){
                    p++;
                }
            }
        }
        }
        if(k==1){
            detect(hint1_x,hint1_y)->lscore%=10;
            detect(hint2_x,hint2_y)->lscore%=10;
            hint1_x=-1;
            hint1_y=-1;
            hint2_x=-1;
            hint2_y=-1;
        }//两个hint的blocks其中有一个被消除
    else{
           if(hint1_x==-1||k==0){
               bool flag=false;
               for(int i=1;i<=length1;i++){
                   for(int j=1;j<=length1;j++){
                       if(detect(i,j)->lscore>0&&detect(i,j)->lscore<10){
                           for(int m=i;m<=length1;m++){
                               for(int n=1;n<=length1;n++){
                                   if(!(m==i&&n==j)){
                                       if(detect(m,n)->lscore>0&&detect(m,n)->lscore<10&&(whetherlink(i,j,m,n))){
                                           hint1_x=i;
                                           hint1_y=j;
                                           hint2_x=m;
                                           hint2_y=n;
                                           flag=true;
                                       }if(flag) break;
                                   }if(flag) break;
                               }if(flag) break;
                           }if(flag) break;
                       }if(flag) break;
                   }if(flag) break;
               }
               detect(hint1_x,hint1_y)->lscore+=20;
               detect(hint2_x,hint2_y)->lscore+=20;
           }
       }
    }
    if(hint_time==0){
        if (hint_ending){
            detect(hint1_x,hint1_y)->lscore%=10;
            detect(hint2_x,hint2_y)->lscore%=10;
            if((former1_x==hint1_x&&former1_y==hint1_y)||(former1_x==hint2_x&&former1_y==hint2_y)){
                former1_x=-1;
                former1_y=-1;
                single1=false;
            }
            if((former2_x==hint1_x&&former2_y==hint1_y)||(former2_x==hint2_x&&former2_y==hint2_y)){
                former2_x=-1;
                former2_y=-1;
                single2=false;
            }
            hint1_x=-1;
            hint1_y=-1;
            hint2_x=-1;

            hint2_y=-1;
        }
        hint_ending = 0;
    }
}

void double_mode::dehint(){
    hint_time=false;
}

void double_mode::dizzy(int member){
    if(member==1){
        player2_dizzy=1;
    }
    if(member==2){
        player1_dizzy=1;
    }
}
void double_mode::dedizzy(){
     if(player1_dizzy==1){
         player1_dizzy=0;
     }
     if(player2_dizzy){
         player2_dizzy=0;
     }
}

void double_mode::freeze(int member){
    if(member==1){
        player2_freezing=1;
    }
    if(member==2){
        player1_freezing=1;
    }
}
void double_mode::defreeze(){
     if(player2_freezing){
         player2_freezing=0;
     }
     if(player1_freezing){
         player1_freezing=0;
     }
}




void double_mode::on_pushButton_4_clicked()
{
    if (pause_flag){
        _1stimer->stop();
        timer->stop();
        pause_flag = 0;
        ui->pushButton->setText("continue");
    }
    QString fileName = QFileDialog::getSaveFileName(this);
    if (!fileName.isEmpty()){
        QFile file(fileName);
        file.open(QIODevice::Truncate | QIODevice::WriteOnly);
        QDataStream out(&file);
        for(int i=0;i<(length1+2)*(length1+2);i++){
            out<<block[i].x<<block[i].y<<block[i].lscore;
        }
        out<<player1_x<<player1_y<<single1<<score1<<former1_x<<former1_y;
        out<<hint_time<<hint_ending<<timee1<<timee2;
        out<<hint1_x<<hint1_y<<hint2_x<<hint2_y;
        out<<player2_x<<player2_y<<single2<<score2<<former2_x<<former2_y;
    }
}

void double_mode::on_pushButton_3_clicked()
{
    if (pause_flag){
        _1stimer->stop();
        timer->stop();
        pause_flag = 0;
        ui->pushButton->setText("continue");
    }
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()){
        QFile file(fileName);
        file.open(QIODevice::Truncate | QIODevice::ReadOnly);
        QDataStream in(&file);
        for(int i=0;i<(length1+2)*(length1+2);i++){
            in>>block[i].x>>block[i].y>>block[i].lscore;
        }
        in>>player1_x>>player1_y>>single1>>score1>>former1_x>>former1_y;
        in>>hint_time>>hint_ending>>timee1>>timee2;
        in>>hint1_x>>hint1_y>>hint2_x>>hint2_y;
        in>>player2_x>>player2_y>>single2>>score2>>former2_x>>former2_y;
        pause_flag = 0;
        timer->stop();
        _1stimer->stop();
        ui->lcdNumber->display(score1);
        ui->lcdNumber_2->display(score2);
        ui->pushButton->setText("continue");
        ui->lcdNumber_3->display(timee1);
        ui->lcdNumber_4->display(timee2);
    }
}

void double_mode::on_pushButton_2_clicked()
{
    this->hide();
    this->endGame();
}

void double_mode::on_pushButton_clicked()
{
    if (pause_flag){
        _1stimer->stop();
        timer->stop();
        pause_flag = 0;
        ui->pushButton->setText("continue");
    }
    else{
        _1stimer->start();
        timer->start();
        pause_flag = 1;
        ui->pushButton->setText("pause");
    }
}
