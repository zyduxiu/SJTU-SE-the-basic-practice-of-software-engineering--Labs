#ifndef SUCCESS_H
#define SUCCESS_H

#include <QWidget>

namespace Ui {
class success;
}

class success : public QWidget
{
    Q_OBJECT

public:
    explicit success(QWidget *parent = nullptr);
    ~success();
    bool ignore=false;
private slots:
    void ignorewidget();
private:
    Ui::success *ui;
};

#endif // SUCCESS_H
