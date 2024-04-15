#include "end2.h"
#include "ui_end2.h"
#include "mainwindow.h"
#include "double_mode.h"
end2::end2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::end2)
{
    this->setObjectName("end_2");
    this->setStyleSheet("#end_2{border-image:url(:/resources/main.jpg);}");
    ui->setupUi(this);
}

end2::~end2()
{
    delete ui;
}

void end2::on_pushButton_clicked()
{
    MainWindow *st=new MainWindow;
    st->show();
    this->hide();
}

void end2::on_pushButton_2_clicked()
{
    QApplication* app;
    app->exit(0);
}
