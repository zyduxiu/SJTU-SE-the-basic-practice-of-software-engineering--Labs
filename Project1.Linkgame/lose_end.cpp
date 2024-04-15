#include "lose_end.h"
#include "ui_lose_end.h"
#include "single_modee.h"
#include "mainwindow.h"
lose_end::lose_end(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lose_end)
{
    this->setObjectName("lose_end");
    this->setStyleSheet("#lose_end{border-image:url(:/resources/main.jpg);}");
    ui->setupUi(this);
}

lose_end::~lose_end()
{
    delete ui;
}

void lose_end::on_pushButton_clicked()
{
    MainWindow *st=new MainWindow;
    st->show();
    this->hide();
}

void lose_end::on_pushButton_2_clicked()
{
    QApplication* app;
    app->exit(0);
}
