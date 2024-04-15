#include "single_mode.h"
#include "window.h"
#include <vector>
#include "victory_end.h"
#include "lose_end.h"
#include "end.h"
#include "pause.h"
#include <QSound>
#include "single_modee.h"
#include "ui_single_modee.h"
#include "mainwighet.h"
#include "ui_lose_end.h"
#include <QDebug>
single_modee::single_modee(QWidget *parent)
    : QMainWindow(parent),
    ui (new Ui::single_modee)
{
    timee=totaltime;
    ui->setupUi(this);
    this->setObjectName("single_mode");
    this->setStyleSheet("#single_mode{border-image:url(:/resources/grass.jpg);}");
    hint_time = 0;
    hint_ending = 0;
    ui->scores->setDigitCount(3);
    ui->scores->setDecMode();
    ui->lcdNumber->setDigitCount(3);
    ui->lcdNumber->setDecMode();
    _1stimer->start(1000);

    connect(_1stimer,SIGNAL(timeout()),this,SLOT(timedecrease()));//倒计时槽函数
   // _1stimer->start(1000);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&single_mode::repaint));//实时更新画面的函数
    // connect(timer,SIGNAL(timeout()),this,SLOT(paintEvent()));
    connect(timer, SIGNAL(timeout()), this, SLOT(showthing()));
    timer->start(20);
    connect(timer, SIGNAL(timeout()), this, SLOT(hint()));

    pause_flag = 1;
    ui->pushButton->setText("pause");
    qsrand(QTime::currentTime().msec());
    int s=0;
        for(int j=0;j<length+2;j++){
            for(int k=0;k<length+2;k++){
                if(j==0||k==0||j==length+1||k==length+1){
                    block[s].lscore=0;
                    block[s].x=k;
                    block[s].y=j;//定义地图四周的白边
                }
                else{
                    block[s].lscore=qrand()%9+1;
                    block[s].x=k;
                    block[s].y=j;//随机分配构建地图
                }
                s++;
            }
        }

    for(int i=0;i<4;i++){
        bool flag=true;
        int a=qrand()%length+1;
        int b=qrand()%length+1;
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
            detect(a,b)->lscore=i+100;//分配道具
        }
    }
    if(length<6){
        for(int i=0;i<length+2;i++){
            for(int j=0;j<length+2;j++){
                if(detect(i,j)->lscore==102){
                    int k=qrand()%9+1;
                    detect(i,j)->lscore=k;//处理特殊情况
                }
            }
        }
    }
    player_x=0;
    player_y=0;
    DEAD();
    }

point* single_modee::detect(int a,int b){
    for(int i=0;i<(length+2)*(length+2);i++){
        if(block[i].x==a&&block[i].y==b){
            return &block[i];
        }
    }
}

void single_modee::timedecrease(){
    if(timee<=0)
    {
        _1stimer->stop();
        timer->stop();
        lose_end*st=new lose_end;
        st->show();
        this->hide();
    }
    timee--;
}

void single_modee::showthing()
{
    ui->scores->display(score);
    ui->lcdNumber->display(timee);
}


void single_modee::endGame()
{
    timer->stop();
    end *st=new end;
    st->show();
    this->hide();
}

single_modee::~single_modee()
{
    delete ui;
}

void single_modee::delay(int time)
{
    QEventLoop loop;//定义一个循环的线程
    QTimer::singleShot(time, &loop, SLOT(quit()));
    loop.exec();
}

void single_modee::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    for(int k=0;k<(length+2)*(length+2);k++){
        int x=100*block[k].x+360;
        int y=100*block[k].y+100;
            QPixmap icon;
            if(block[k].lscore!=0){
                if(block[k].lscore==1){
                   icon.load(":/resources/ball1.png");
                }
                if(block[k].lscore==2){
                   icon.load(":/resources/ball2.png");
                }
                if(block[k].lscore==3){
                   icon.load(":/resources/ball3.png");
                }
                if(block[k].lscore==4){
                   icon.load(":/resources/ball4.png");
                }
                if(block[k].lscore==5){
                   icon.load(":/resources/ball5.png");
                }
                if(block[k].lscore==6){
                   icon.load(":/resources/ball6.png");
                }
                if(block[k].lscore==7){
                   icon.load(":/resources/ball7.png");
                }
                if(block[k].lscore==8){
                   icon.load(":/resources/ball8.png");
                }
                if(block[k].lscore==9){
                   icon.load(":/resources/ball9.png");
                }
                if(block[k].lscore==11){
                   icon.load(":/resources/ball1_1.png");
                }
                if(block[k].lscore==12){
                   icon.load(":/resources/ball2_1.png");
                }
                if(block[k].lscore==13){
                   icon.load(":/resources/ball3_1.png");
                }
                if(block[k].lscore==14){
                   icon.load(":/resources/ball4_1.png");
                }
                if(block[k].lscore==15){
                   icon.load(":/resources/ball5_1.png");
                }
                if(block[k].lscore==16){
                   icon.load(":/resources/ball6_1.png");
                }
                if(block[k].lscore==17){
                   icon.load(":/resources/ball7_1.png");
                }
                if(block[k].lscore==18){
                   icon.load(":/resources/ball8_1.png");
                }
                if(block[k].lscore==19){
                   icon.load(":/resources/ball9_1.png");
                }
                if(block[k].lscore==21){
                    icon.load(":/resources/ball1_2.png");
                 }
                if(block[k].lscore==22){
                   icon.load(":/resources/ball2_2.png");
                }
                if(block[k].lscore==23){
                   icon.load(":/resources/ball3_2.png");
                }
                if(block[k].lscore==24){
                   icon.load(":/resources/ball4_2.png");
                }
                if(block[k].lscore==25){
                   icon.load(":/resources/ball5_2.png");
                }
                if(block[k].lscore==26){
                   icon.load(":/resources/ball6_2.png");
                }
                if(block[k].lscore==27){
                   icon.load(":/resources/ball7_2.png");
                }
                if(block[k].lscore==28){
                   icon.load(":/resources/ball8_2.png");
                }
                if(block[k].lscore==29){
                   icon.load(":/resources/ball9_2.png");
                }
                if(block[k].lscore==1000){
                   icon.load(":/resources/N_S.png");
                }
                if(block[k].lscore==1001){
                   icon.load(":/resources/W_E.png");
                }
                if(block[k].lscore==1002){
                   icon.load(":/resources/S_E.png");
                }
                if(block[k].lscore==1003){
                   icon.load(":/resources/N_E.png");
                }
                if(block[k].lscore==1004){
                   icon.load(":/resources/W_N.png");
                }
                if(block[k].lscore==1005){
                   icon.load(":/resources/W_S.png");
                }
                if(block[k].lscore==100){
                   icon.load(":/resources/shuffle.png");
                }
                if(block[k].lscore==101){
                   icon.load(":/resources/plus.png");
                }
                if(block[k].lscore==102){
                   icon.load(":/resources/hint.png");
                }
                if(block[k].lscore==103){
                   icon.load(":/resources/flash.png");
                }
            painter.drawPixmap(x,y,100,100,icon);
            }
    }
    user.load(":/resources/user.jpg");
    int a=370+100*player_x;
    int b=100+100*player_y;
    painter.drawPixmap(a,b,80,80,user);//绘制
    painter.end();
}

void single_modee::keyPressEvent(QKeyEvent *event)
{
    if (pause_flag){
        if (Qt::Key_A == event->key()){
            left_chooseBlock();
            player_x -=1;
        }
        if (Qt::Key_D == event->key()){
            right_chooseBlock();
            player_x +=1;
        }
        if (Qt::Key_W == event->key()){
            up_chooseBlock();
            player_y -=1;
        }
        if (Qt::Key_S == event->key()){
            down_chooseBlock();
            player_y +=1;
        }
    }
}

void single_modee::left_chooseBlock(){
    if(player_x<=0) {player_x+=1;}
    int i = player_x;
    int j = player_y;
    if (player_x>=0 && player_x <= length+1 && player_y>=0 &&player_y <= length+1)//判断是否在地图范围内
        if (detect(i,j)->lscore>=100&&detect(i,j)->lscore<110){
            int tool=detect(i,j)->lscore;
            detect(i,j)->lscore = 0;
            tool_s(tool);
        }
    int a = -1 ,b = -1;
    a = i-1;
    b = j;
    if (a >= 1 && a <= length && b >= 1 && b <= length){
        if((detect(a,b)->lscore>0&&detect(a,b)->lscore<100)){
        player_x+=1;}
        if((detect(a,b)->lscore>0&&detect(a,b)->lscore<10)||(detect(a,b)->lscore>20&&detect(a,b)->lscore<30)){
            detect(a,b)->lscore=(detect(a,b)->lscore)%10+10;
            if(!single){//没有选中过block的情况
                single=true;
                former_x=a;
                former_y=b;
            }
            else{
                if(whetherlink(former_x,former_y,a,b)){
                    link(former_x,former_y,a,b);
                    score+=(detect(a,b)->lscore)%10;
                    eliminate(former_x,former_y,a,b,1);
                    Dead();
                }
                else{
                    detect(former_x,former_y)->lscore=(detect(former_x,former_y)->lscore)%10;
                    detect(a,b)->lscore%=10;
                    if(hint1_x!=-1){
                        if(detect(hint1_x,hint1_y)->lscore>0&&detect(hint1_x,hint1_y)->lscore<10){
                            detect(hint1_x,hint1_y)->lscore+=20;//防止hint的block被消除
                        }
                        if(detect(hint2_x,hint2_y)->lscore>0&&detect(hint2_x,hint2_y)->lscore<10){
                            detect(hint2_x,hint2_y)->lscore+=20;
                        }
                    }
                }
                single=false;
            }
        }
    }
}

void single_modee::right_chooseBlock(){
    if(player_x >= length+1){player_x-=1;}
    int i = player_x;
    int j = player_y;
    if (player_x>=0 && player_x <= length+1 && player_y>=0 &&player_y <= length+1)
        if (detect(i,j)->lscore>=100&&detect(i,j)->lscore<110){
            int tool=detect(i,j)->lscore;
            detect(i,j)->lscore = 0;
            tool_s(tool);
        }
    int a = -1 ,b = -1;
        a = i+1;
        b = j;
    if (a >= 1 && a <= length && b >= 1 && b <= length){
        if((detect(a,b)->lscore>0&&detect(a,b)->lscore<100)){
        player_x-=1;}
        if((detect(a,b)->lscore>0&&detect(a,b)->lscore<10)||(detect(a,b)->lscore>20&&detect(a,b)->lscore<30)){
            detect(a,b)->lscore=(detect(a,b)->lscore)%10+10;
            if(!single){
                single=true;
                former_x=a;
                former_y=b;
            }
            else{
                if(whetherlink(former_x,former_y,a,b)){
                    link(former_x,former_y,a,b);
                    score+=detect(a,b)->lscore%10;
                    eliminate(former_x,former_y,a,b,2);
                    Dead();
                }
                else{
                    detect(former_x,former_y)->lscore=detect(former_x,former_y)->lscore%10;
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
                single=false;
            }
        }
    }
}

void single_modee::up_chooseBlock(){
    if(player_y<=0){player_y+=1;}
    int i = player_x;
    int j=  player_y;
    if (player_x>=0 && player_x <= length+1 && player_y>=0 &&player_y <= length+1)
        if (detect(i,j)->lscore>=100&&detect(i,j)->lscore<110){
            int tool=detect(i,j)->lscore;
            detect(i,j)->lscore = 0;
            tool_s(tool);
        }
    int a=-1,b=-1;
    a=i;
    b=j-1;
    if (a >= 1 && a <= length && b >= 1 && b <= length){
        if((detect(a,b)->lscore>0&&detect(a,b)->lscore<100)){
        player_y+=1;}
        if((detect(a,b)->lscore>0&&detect(a,b)->lscore<10)||(detect(a,b)->lscore>20&&detect(a,b)->lscore<30)){
            detect(a,b)->lscore=(detect(a,b)->lscore)%10+10;
            if(!single){
                single=true;
                former_x=a;
                former_y=b;
            }
            else{
                if(whetherlink(former_x,former_y,a,b)){
                    link(former_x,former_y,a,b);
                    score+=detect(a,b)->lscore%10;
                    eliminate(former_x,former_y,a,b,3);
                    Dead();
                }
                else{
                    detect(former_x,former_y)->lscore=detect(former_x,former_y)->lscore%10;
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
            single=false;
        }
    }
    }
}
void single_modee::down_chooseBlock(){
    if(player_y>=length+1){player_y-=1;}
    int i = player_x;
    int j=  player_y;
    if (player_x>=0 && player_x <= length+1 && player_y>=0 &&player_y <= length+1)
        if (detect(i,j)->lscore>=100&&detect(i,j)->lscore<110){
            int tool=detect(i,j)->lscore;
            detect(i,j)->lscore = 0;
            tool_s(tool);
        }
    int a = -1 ,b = -1;
        a = i;
        b = j+1;
    if (a >= 1 && a <= length && b >= 1 && b <= length){
        if(detect(a,b)->lscore>0&&detect(a,b)->lscore<100){
            player_y-=1;
        }
        if((detect(a,b)->lscore>0&&detect(a,b)->lscore<10)||(detect(a,b)->lscore>20&&detect(a,b)->lscore<30)){
            detect(a,b)->lscore=(detect(a,b)->lscore)%10+10;
            if(!single){
                single=true;
                former_x=a;
                former_y=b;
            }
            else{
                if(whetherlink(former_x,former_y,a,b)){
                    link(former_x,former_y,a,b);
                    score+=detect(a,b)->lscore%10;
                    eliminate(former_x,former_y,a,b,4);
                    Dead();
                }
                else{
                    detect(former_x,former_y)->lscore=detect(former_x,former_y)->lscore%10;
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
                single=false;
            }
        }
    }
}

void single_modee::tool_s(int tool){
    if(tool==101){
        plus();
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
        flash_flag=true;
        QTimer::singleShot(10000,this,SLOT(deflash()));
    }
    Dead();
}




int single_modee::whethercanflash(int x, int y){
    if((x<200||x>1500)||((y>1250)||(y<100))){
            return 0;
}
    int i=(x-350)/100;
    int j=(y-110)/100;
    if((i<0)||(i>length)||(j<0)||(j>length)||((detect(i,j)->lscore==0))){
        return 0;
    }
    else{
        if(detect(i-1,j)->lscore==0){
            return 2;
        }
        if(detect(i+1,j)->lscore==0){
            return 3;
        }
        if(detect(i,j-1)->lscore==0){
            return 4;
        }
        if(detect(i,j+1)->lscore==0){
            return 5;
        }
        return 0;
    }
}

void single_modee::mousePressEvent(QMouseEvent *eve){
    if(flash_flag){
        if(whethercanflash(eve->x(),eve->y())!=0){
            int i=(eve->x()-360)/100;
            int j=(eve->y()-100)/100;
            if(whethercanflash(eve->x(),eve->y())==1){
                player_x=eve->x();
                player_y=eve->y();
            }
            if(whethercanflash(eve->x(),eve->y())==2){
                player_x=i-1;
                player_y=j;
            }
            if(whethercanflash(eve->x(),eve->y())==3){
                player_x=i+1;
                player_y=j;
            }
            if(whethercanflash(eve->x(),eve->y())==4){
                player_x=i;
                player_y=j-1;
            }
            if(whethercanflash(eve->x(),eve->y())==5){
                player_x=i;
                player_y=j+1;
            }
            flash_flag=false;
        }
    }
}

void single_modee::deflash(){
    flash_flag=false;
}



bool single_modee::straightwhetherlink(int ax, int ay, int bx, int by)
{
    if (((detect(ax,ay)->lscore%10) != (detect(bx,by)->lscore%10))//两端block种类不一样
            &&(!(detect(ax,ay)->lscore%10!=0&&detect(bx,by)->lscore==0))//一端为空
            &&(!(detect(ax,ay)->lscore==0&&detect(bx,by)->lscore==0))
            &&(!(detect(ax,ay)->lscore==0&&detect(bx,by)->lscore !=0))){
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

void single_modee::eliminate(int ax, int ay, int bx, int by,int i)
{
    detect(ax,ay)->lscore = 0;
    detect(bx,by)->lscore = 0;
    Dead();
}

bool single_modee::whetherlink(int ax,int ay,int bx,int by){
    if((detect(ax,ay)->lscore%10)!=(detect(bx,by)->lscore%10)){
        return false;
    }
    for(int i=0;i<length+2;i++){
        //最多折三段折线相连
        if(straightwhetherlink(ax,ay,i,ay)&&straightwhetherlink(i,ay,i,by)
                &&straightwhetherlink(bx,by,i,by)){
            return true;
        }
    }
    for(int i=0;i<length+2;i++){
        if(straightwhetherlink(ax,ay,i,ay)&&straightwhetherlink(i,ay,i,by)
                &&straightwhetherlink(i,by,bx,by)){
            return true;
        }
    }
    for(int i=0;i<length+2;i++){
        if(straightwhetherlink(ax,ay,ax,i)&&straightwhetherlink(ax,i,bx,i)
                &&straightwhetherlink(bx,i,bx,by)){
            return true;
        }
    }
    for(int i=0;i<length+2;i++){
        if(straightwhetherlink(ax,ay,ax,i)&&straightwhetherlink(ax,i,bx,i)
                &&straightwhetherlink(bx,i,bx,by)){
            return true;
        }
    }
    return false;
}

void single_modee::straightlink(int ax, int ay, int bx, int by){
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

void single_modee::de_straightlink(int ax, int ay, int bx, int by){
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

void single_modee::link(int ax, int ay, int bx, int by){
    if((ax==bx||ay==by)&&straightwhetherlink(ax,ay,bx,by)){
        straightlink(ax,ay,bx,by);//直接相连
    }
    else{
        if(ax<bx){
            if(ay>by){//一次折线
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
        }//两次折线
            for(int i=0;i<length+2;i++){
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
                            detect(ax,i)->lscore=1004;
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


void single_modee::DEAD(){
            bool ifdead=true;
            for (int i=1; i<=length; i++){
                for (int j=1; j<=length; j++){
                    if (detect(i,j)->lscore!=0){
                        for (int k=i; k<=length; k++){
                            for (int l=1; l<=length; l++){
                                if (!(k==i&&l==j))
                                    if (whetherlink(i,j,k,l)){//避免两点共点
                                        ifdead=false;
                                        break;
                                    }
                            }
                        }
                    }
                }
            }
            if (ifdead){
                timer->stop();
                victory_end *st=new victory_end;
                st->show();
                this->hide();
            }
}
void single_modee::Dead()
{
    bool ifdead=true;
    for (int i=1; i<=length; i++){
        for (int j=1; j<=length; j++){
            if (detect(i,j)->lscore!=0){
                for (int k=i; k<=length; k++){
                    for (int l=1; l<=length; l++){
                        if (!(k==i&&l==j))
                            if (whetherlink(i,j,k,l)){
                                ifdead=false;
                                break;
                            }
                    }
                }
            }
        }
    }
    for(int i=1;i<=length;i++){
        for(int j=1;j<=length;j++){
            if(detect(i,j)->lscore>100&&detect(i,j)->lscore<110){
                ifdead=false;
            }
        }
    }
    if (ifdead){
        timer->stop();
        victory_end *st=new victory_end;
        st->show();
        this->hide();
    }
}

void single_modee::plus()
{
    if (timee>=totaltime-30){
        timee=totaltime;
    }
    else{
        timee+=30;
    }
}

void single_modee::shuffle(){
    single=false;
    std::vector<int> a;
    for(int i=1;i<=length;i++){
        for(int j=1;j<=length;j++){
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
        int z=qrand()%length+1;
        int x=qrand()%length+1;
        bool flag=true;
        if(detect(z,x)->lscore!=0){
            flag=false;//跳过已经分配的block
        }
        if(detect(z,x)->lscore>100&&detect(z,x)->lscore<110){
            flag=false;
        }
        if(!flag){w--;}
        else{
                detect(z,x)->lscore=a[w];//随机重新分配已经存在的blocks
        }
    }
    hint1_x=-1;
    hint1_y=-1;
    hint2_x=-1;
    hint2_y=-1;
    player_x=0;
    player_y=0;
}


void single_modee::hint()
{
    DEAD();
    if(hint_time==1){
        int k=0;int p=0;
        if(hint1_x!=-1){
        if(detect(hint1_x,hint1_y)->lscore!=0){
            k++;
        }
        if(detect(hint2_x,hint2_y)->lscore!=0){
            k++;
        }
        for(int i=1;i<=length;i++){
            for(int j=1;j<=length;j++){
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
            hint2_y=-1;//在hint的两个blocks有一个被消除的情况下重新分配hint
        }
    else{
           if(hint1_x==-1||k==0){
               bool flag=false;
               for(int i=1;i<=length;i++){
                   for(int j=1;j<=length;j++){
                       if(detect(i,j)->lscore>0&&detect(i,j)->lscore<10){
                           for(int m=i;m<=length;m++){
                               for(int n=1;n<=length;n++){
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
    if (hint_time==0){
        if (hint_ending){
            detect(hint1_x,hint1_y)->lscore%=10;
            detect(hint2_x,hint2_y)->lscore%=10;
            if((former_x==hint1_x&&former_y==hint1_y)||(former_x==hint2_x&&former_y==hint2_y)){
                former_x=-1;
                former_y=-1;
                single=false;
            }
            hint1_x=-1;
            hint1_y=-1;
            hint2_x=-1;
            hint2_y=-1;
        }
        hint_ending = 0;
    }
}

void single_modee::dehint(){
    hint_time=false;
    for(int i=0;i<(length+2)*(length+2);i++){
        if(single==1){
            detect(former_x,former_y)->lscore+=10;
        }
    }
}


void single_modee::on_pushButton_2_clicked()
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
        for(int i=0;i<(length+2)*(length+2);i++){
            out<<block[i].x<<block[i].y<<block[i].lscore;
        }
        out<<player_x<<player_y<<single<<score<<former_x<<former_y;
        out<<hint_time<<hint_ending<<flash_flag<< timee;
        out<<hint1_x<<hint1_y<<hint2_x<<hint2_y;
    }
}

void single_modee::on_pushButton_3_clicked()
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
        for(int i=0;i<(length+2)*(length+2);i++){
            in>>block[i].x>>block[i].y>>block[i].lscore;
        }
        in>>player_x>>player_y>>single>>score>>former_x>>former_y;
        in>>hint_time>>hint_ending>>flash_flag>>timee;
        in>>hint1_x>>hint1_y>>hint2_x>>hint2_y;
        pause_flag = 0;
        timer->stop();
        _1stimer->stop();
        ui->scores->display(score);
        ui->pushButton->setText("continue");
        ui->lcdNumber->display(timee);
    }
}


void single_modee::on_pushButton_4_clicked()
{
    this->hide();
    this->endGame();
}

void single_modee::on_pushButton_clicked()
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
