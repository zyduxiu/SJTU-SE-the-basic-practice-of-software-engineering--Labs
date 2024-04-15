#include "mainwighet.h"
#include "ui_mainwighet.h"
#include "single_modee.h"
#include "double_mode.h"
mainwighet::mainwighet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainwighet)
{
    this->setObjectName("mainwighet");
    this->setStyleSheet("#mainwighet{border-image:url(:/resources/main.jpg);}");
    st->play();
    st->setLoops(10);
    ui->setupUi(this);
}

mainwighet::~mainwighet()
{
    delete ui;
}

void mainwighet::on_pushButton_clicked()
{
    single_modee *st=new single_modee;
    st->show();
}

void mainwighet::on_pushButton_2_clicked()
{
    double_mode *st=new double_mode;
    st->show();
}
