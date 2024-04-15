#ifndef MAINWIGHET_H
#define MAINWIGHET_H

#include <QWidget>
#include <QSound>
namespace Ui {
class mainwighet;
}

class mainwighet : public QWidget
{
    Q_OBJECT

public:
    explicit mainwighet(QWidget *parent = nullptr);
    ~mainwighet();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    QSound *st=new QSound(":/resources/xiyangyang.wav");
    Ui::mainwighet *ui;
};

#endif // MAINWIGHET_H
