#ifndef WRONGFILE_H
#define WRONGFILE_H

#include <QWidget>

namespace Ui {
class wrongfile;
}

class wrongfile : public QWidget
{
    Q_OBJECT

public:
    explicit wrongfile(QWidget *parent = nullptr);
    ~wrongfile();

private:
    Ui::wrongfile *ui;
};

#endif // WRONGFILE_H
