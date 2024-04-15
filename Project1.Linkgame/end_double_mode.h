#ifndef END_DOUBLE_MODE_H
#define END_DOUBLE_MODE_H

#include <QWidget>

namespace Ui {
class end_double_mode;
}

class end_double_mode : public QWidget
{
    Q_OBJECT

public:
    explicit end_double_mode(QWidget *parent = nullptr);
    ~end_double_mode();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::end_double_mode *ui;
};

#endif // END_DOUBLE_MODE_H
