#include "end_double_mode.h"
#include "ui_end_double_mode.h"
#include "double_mode.h"
#include "mainwindow.h"
end_double_mode::end_double_mode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::end_double_mode)
{
    ui->setupUi(this);
}

end_double_mode::~end_double_mode()
{
    delete ui;
}

void end_double_mode::on_pushButton_clicked()
{
    this->setObjectName("end3");
    this->setStyleSheet("#end3{border-image:url(:/resources/main.jpg);}");
    MainWindow*st=new MainWindow;
    st->show();
    this->hide();
}

void end_double_mode::on_pushButton_2_clicked()
{
    QApplication* app;
    app->exit(0);
}
