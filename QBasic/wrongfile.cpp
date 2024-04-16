#include "wrongfile.h"
#include "ui_wrongfile.h"

wrongfile::wrongfile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wrongfile)
{
    ui->setupUi(this);
}

wrongfile::~wrongfile()
{
    delete ui;
}
