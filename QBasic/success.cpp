#include "success.h"
#include "ui_success.h"

success::success(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::success)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(ignorewidget()));
}

void success::ignorewidget(){
    ignore=true;
    this->hide();
}
success::~success()
{
    delete ui;
}
