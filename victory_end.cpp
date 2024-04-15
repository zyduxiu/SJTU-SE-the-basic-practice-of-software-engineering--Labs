
#include "victory_end.h"
#include "ui_victory_end.h"
#include "single_modee.h"
#include "mainwindow.h"
victory_end::victory_end(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::victory_end)
{
    this->setObjectName("victory_end");
    this->setStyleSheet("#victory_end{border-image:url(:/resources/main.jpg);}");
    ui->setupUi(this);
}

victory_end::~victory_end()
{
    delete ui;
}

void victory_end::on_pushButton_clicked()
{
    MainWindow *st=new MainWindow;
    st->show();
    this->hide();
}

void victory_end::on_pushButton_2_clicked()
{
    QApplication* app;
    app->exit(0);
}
