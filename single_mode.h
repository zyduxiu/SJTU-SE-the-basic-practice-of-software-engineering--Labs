#ifndef SINGLE_MODEE_H
#define SINGLE_MODEE_H

#include <QMainWindow>
#include <iostream>
#include <QMainWindow>
#include <QMenuBar>
#include <QFileDialog>
#include <QtWidgets>
#include<stdio.h>
#include<stdlib.h>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QSound>
#include "mainwighet.h"
namespace Ui {
class single_modee;
}
const int length=4;//single mode的地图大小
const int totaltime=20;//single mode的游戏总时长
struct point/*定义点类*/{
    int x;//横坐标
    int y;//纵坐标
    int lscore=0;//block的种类
};
class single_modee : public QMainWindow
{
    Q_OBJECT

public:
    single_modee(QWidget *parent = nullptr);
    ~single_modee();
    void paintEvent(QPaintEvent *event) override;//绘画函数
    virtual void keyPressEvent(QKeyEvent *event) override;//keypressevent的槽函数
    virtual void mousePressEvent(QMouseEvent *ev) override;//mousepressevent的槽函数
    void up_chooseBlock();
    void down_chooseBlock();
    void left_chooseBlock();
    void right_chooseBlock();
    int player_x=0;//player的横坐标
    int player_y=0;//player的纵坐标
    point block[(length+2)*(length+2)];//block的一维数组
    bool hint_time;//hint的倒计时时长
    bool hint_ending;//表示是否处于hint过程中
    bool whetherlink(int ax, int ay, int bx, int by);//判断是否相连
    bool straightwhetherlink(int ax,int ay,int bx,int by);//判断是否直连
    void eliminate(int ax, int ay, int bx, int by,int i);//消除函数
    void Dead();//判断是否死局
    void delay(int i);//延迟函数
    void link(int ax, int ay, int bx, int by);//连线函数
    void straightlink(int ax, int ay, int bx, int by);//连直线函数
    void de_straightlink(int ax,int ay,int bx, int by);
    //void iflink(int fx,int fy,int x,int y);
    int whethercanflash(int x,int y);//是否可以位移的函数
    point* detect(int a,int b);//辅助函数
    void DEAD();
private:
    Ui::single_modee *ui;
    int timee;
    QTimer *_1stimer=new QTimer;
    QTimer *timer=new QTimer;
    bool pause_flag;
    bool flash_flag=0;
    QPixmap user;
    int score=0;
    bool single=false;
    int former_x=0;//former block
    int former_y=0;
    int hint1_x=-1;//hint block
    int hint1_y=-1;
    int hint2_x=-1;
    int hint2_y=-1;
protected:

private slots:
    //void timeend();
    void endGame();
    void showthing();
    void timedecrease();//倒计时函数
    void hint();
    void dehint();
    void plus();
    //void flash();
    void tool_s(int tool);
    void shuffle();
    void deflash();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_clicked();
};

#endif // SINGLE_MODEE_H
