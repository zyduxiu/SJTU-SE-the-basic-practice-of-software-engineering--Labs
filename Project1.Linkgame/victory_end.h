#ifndef VICTORY_END_H
#define VICTORY_END_H

#include <QWidget>

namespace Ui {
class victory_end;
}

class victory_end : public QWidget
{
    Q_OBJECT

public:
    explicit victory_end(QWidget *parent = nullptr);
    ~victory_end();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::victory_end *ui;
};

#endif // VICTORY_END_H
