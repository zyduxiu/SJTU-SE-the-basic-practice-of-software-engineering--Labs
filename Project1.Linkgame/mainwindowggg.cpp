#include "mainwindowggg.h"
#include "ui_mainwindowggg.h"

MainWindowggg::MainWindowggg(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowggg)
{
    ui->setupUi(this);
}

MainWindowggg::~MainWindowggg()
{
    delete ui;
}
