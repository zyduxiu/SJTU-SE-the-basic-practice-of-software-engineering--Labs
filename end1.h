#ifndef END1_H
#define END1_H

#include <QWidget>

namespace Ui {
class end1;
}

class end1 : public QWidget
{
    Q_OBJECT

public:
    explicit end1(QWidget *parent = nullptr);
    ~end1();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::end1 *ui;
};

#endif // END1_H
