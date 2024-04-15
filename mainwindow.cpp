#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "single_modee.h"
#include "double_mode.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setObjectName("mainwindow");
    this->setStyleSheet("#mainwindow{border-image:url(:/resources/main.jpg);}");
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    single_modee *st=new single_modee;
    st->show();
    this->hide();
}

void MainWindow::on_pushButton_2_clicked()
{
    double_mode *st=new double_mode;
    st->show();
    this->hide();
}
