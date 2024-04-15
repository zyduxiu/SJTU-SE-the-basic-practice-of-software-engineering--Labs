#ifndef END2_H
#define END2_H

#include <QWidget>

namespace Ui {
class end2;
}

class end2 : public QWidget
{
    Q_OBJECT

public:
    explicit end2(QWidget *parent = nullptr);
    ~end2();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::end2 *ui;
};

#endif // END2_H
