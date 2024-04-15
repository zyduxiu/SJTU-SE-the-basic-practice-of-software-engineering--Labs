#ifndef MAINWINDOWGGG_H
#define MAINWINDOWGGG_H

#include <QMainWindow>

namespace Ui {
class MainWindowggg;
}

class MainWindowggg : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowggg(QWidget *parent = nullptr);
    ~MainWindowggg();

private:
    Ui::MainWindowggg *ui;
};

#endif // MAINWINDOWGGG_H
