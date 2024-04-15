#ifndef LOSE_END_H
#define LOSE_END_H

#include <QWidget>

namespace Ui {
class lose_end;
}

class lose_end : public QWidget
{
    Q_OBJECT

public:
    explicit lose_end(QWidget *parent = nullptr);
    ~lose_end();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
private:
    Ui::lose_end *ui;
};

#endif // LOSE_END_H
