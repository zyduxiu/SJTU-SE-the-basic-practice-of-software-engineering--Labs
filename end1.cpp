#include "end1.h"
#include "ui_end1.h"
#include "double_mode.h"
#include "mainwindow.h"
end1::end1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::end1)
{
    this->setObjectName("end_1");
    this->setStyleSheet("#end_1{border-image:url(:/resources/main.jpg);}");
    ui->setupUi(this);
}

end1::~end1()
{
    delete ui;
}

void end1::on_pushButton_clicked()
{
    MainWindow *st=new MainWindow;
    st->show();
    this->hide();
}



void end1::on_pushButton_2_clicked()
{
    QApplication* app;
    app->exit(0);
}
