#ifndef END_H
#define END_H

#include <QWidget>

namespace Ui {
class end;
}

class end : public QWidget
{
    Q_OBJECT

public:
    explicit end(QWidget *parent = nullptr);
    ~end();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
private:
    Ui::end *ui;
};

#endif // END_H
