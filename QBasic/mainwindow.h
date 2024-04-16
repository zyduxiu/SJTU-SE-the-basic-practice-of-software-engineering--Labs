#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QVector>
#include <QTimer>
#include <QMainWindow>
#include "program.h"
#include "program_line.h"
#include "variable.h"
#include "statement.h"
#include "statement_tree.h"
#include "expression.h"
#include "statement.h"
#include "success.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int where=0;
    int status=-9999;
private slots:
    void on_cmdLineEdit_editingFinished();
    void immediate_respond(QString str);
    void updatecode();
    void clearall();
    void run();
    void inputsomething();
    void drawsomething();
    void drawexptrees();
    void drawexptree(statement a);
    void adaptsomething(int status);
    void exiting();
    void loadprogram();
    void I_NEED_HELP();
    void removedraw();
    void handleall();
    void update_exptree();
private:
    QVector<int> drawer;
    Ui::MainWindow *ui;
    program *newprogram=new program;
    QTimer *timer=new QTimer;
    bool whetherupdate=true;
    bool immediate=false;
    int printnumber=-2147483648;
    bool printtimes=1;
    statements  statements;
    int adaptline=0;
     bool trigger=false;
     success* successwidget=new success;
};
#endif // MAINWINDOW_H
