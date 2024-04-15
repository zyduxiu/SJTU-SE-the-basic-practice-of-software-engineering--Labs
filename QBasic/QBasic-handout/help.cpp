#include "help.h"
#include "ui_help.h"

HELP::HELP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HELP)
{
    ui->setupUi(this);
}

HELP::~HELP()
{
    delete ui;
}
