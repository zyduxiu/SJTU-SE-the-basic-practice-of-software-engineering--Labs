#ifndef DOUBLE_MODE_H
#define DOUBLE_MODE_H
#include <QTimer>
#include <QMainWindow>
#include <QSound>
#include "mainwighet.h"
namespace Ui {
class double_mode;
}
const int length1=5;//double mode的地图长度
const int totaltime1=10;//double mode的游戏总时长
struct point1/*定义点类*/{
    int x;//x坐标
    int y;//y坐标
    int lscore=0;//block类型
};

class double_mode/*定义doublemode*/ : public QMainWindow
{
    Q_OBJECT

public:
    double_mode(QWidget *parent = nullptr);
    ~double_mode();
    int player1_x=0;
    int player1_y=0;
    int player2_x=0;
    int player2_y=0;
    point1 block[(length1+2)*(length1+2)];//block的一维数组
    bool hint_time;//hint的剩余时长
    bool hint_ending;//表示hint是否结束的bool
    point1* detect(int a,int b);//point的辅助函数
    void paintEvent(QPaintEvent *event) override;//绘画函数
    void keyPressEvent1(QKeyEvent *event) ;//player1的移动事件函数
    void keyPressEvent2(QKeyEvent *event) ;//player2的移动时间函数
    virtual void keyPressEvent(QKeyEvent *event) override;//keypressevent的事件槽函数
    //virtual void mousePressEvent(QMouseEvent *ev) override;
    void up_chooseBlock1();
    void down_chooseBlock1();
    void left_chooseBlock1();
    void right_chooseBlock1();
    void up_chooseBlock2();
    void down_chooseBlock2();
    void left_chooseBlock2();
    bool dead();//判断是否死局
    void right_chooseBlock2();
    bool whetherlink(int ax, int ay, int bx, int by);//判断是否相连
    bool straightwhetherlink(int ax,int ay,int bx,int by);//直连函数
    void eliminate(int ax, int ay, int bx, int by);//消除函数
    void Dead();
    void delay(int i);//延迟函数
    void link(int ax, int ay, int bx, int by);//连线函数
    void straightlink(int ax, int ay, int bx, int by);//直线
    void de_straightlink(int ax,int ay,int bx, int by);
private:
    Ui::double_mode *ui;
    QTimer *_1stimer=new QTimer;
    QTimer *timer=new QTimer;
    bool pause_flag;//判断是否暂停
    int score1=0;//player1的得分总数
    int score2=0;//player2的得分总数
    int timee1=totaltime1;//player1的剩余游戏时间
    int timee2=totaltime1;//player2的剩余游戏时间
    bool single1=false;//判断player1是否已经选定block
    bool single2=false;//判断player2是否已经选定block
    int hint1_x=-1;//hint
    int hint1_y=-1;
    int hint2_x=-1;
    int hint2_y=-1;
    int former1_x=0;//player1已经选定的block
    int former1_y=0;
    int former2_x=0;//player2已经选定的block
    int former2_y=0;
    bool player1_flash=0;
    bool player2_flash=0;
    bool player1_dizzy=0;
    bool player1_freezing=0;
    bool player2_dizzy=0;
    bool player2_freezing=0;
    QPixmap player1_1;
    QPixmap player2_2;

protected:

private slots://槽函数
    void timedecrease();
    void endGame();
    void showthing();
    void hint();
    void dehint();
    void plus(int member);
    void tool_s(int tool,int member);
    void shuffle();
    void dizzy(int member);
    void freeze(int member);
    void defreeze();
    void dedizzy();
    void deflash();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
};


#endif // DOUBLE_MODE_H
