#include "single_modee.h"
#include "window.h"
#include "mainwindow.h"
#include <QApplication>
#include <QWindow>
#include <QIcon>
#include <QSound>
#include "test.h"
/*QTEST_MAIN(testlink)*/


int main(int argc, char *argv[])
{
    QSound *st=new QSound(":/resources/xiyangyang.wav");
    st->play();
    st->setLoops(10);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

