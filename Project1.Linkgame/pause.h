#ifndef PAUSE_H
#define PAUSE_H

#include <QWidget>

namespace Ui {
class pause;
}

class pause : public QWidget
{
    Q_OBJECT

public:
    explicit pause(QWidget *parent = nullptr);
    ~pause();

private slots:


private:
    Ui::pause *ui;
};

#endif // PAUSE_H
