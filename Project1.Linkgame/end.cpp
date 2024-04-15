#include "end.h"
#include "ui_end.h"
#include "single_modee.h"
#include "mainwighet.h"
end::end(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::end)
{
    ui->setupUi(this);
}

end::~end()
{
    delete ui;
}
void end::on_pushButton_clicked()
{
    this->setObjectName("end");
    this->setStyleSheet("#end{border-image:url(:/resources/main.jpg);}");
    single_modee *st=new single_modee;
    st->show();
    this->hide();
}

void end::on_pushButton_2_clicked()
{
    QApplication* app;
    app->exit(0);
}
