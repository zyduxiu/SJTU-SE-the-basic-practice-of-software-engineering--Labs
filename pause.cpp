#include "pause.h"
#include "ui_pause.h"
#include "single_mode.h"
pause::pause(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pause)
{
    ui->setupUi(this);
}

pause::~pause()
{
    delete ui;
}



