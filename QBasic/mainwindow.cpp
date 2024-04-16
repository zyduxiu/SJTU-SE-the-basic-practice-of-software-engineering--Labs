#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "program.h"
#include "program_line.h"
#include <vector>
#include <QQueue>
#include <QApplication>
#include <QFile>
#include <QFileDialog>
#include "help.h"
#include "wrongfile.h"
#include "exp_tree.h"
#include "QMessageBox"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer->start(100);
    connect(ui->btnClearCode,SIGNAL(clicked()),this,SLOT(clearall()));//清除代码
    connect(ui->cmdLineEdit,SIGNAL(returnPressed()),this,SLOT(returnpressed()));//输入指令
    connect(ui->btnLoadCode,SIGNAL(clicked()),this,SLOT(returnpressed()));//输入指令
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::repaint));//更新画面
    connect(timer, SIGNAL(timeout), this,SLOT(removedraw()));
    connect(ui->btnRunCode,SIGNAL(clicked()),this,SLOT(run()));//运行程序

    connect(ui->btnLoadCode,SIGNAL(clicked()),this,SLOT(loadprogram()));//读取txt文档

}

void MainWindow::removedraw(){
    ui->textBrowser->clear();
  //  drawsomething();

}

void MainWindow::update_exptree(){
    ui->treeDisplay->clear();//清楚语法树部分
//    for(int i=0;i<statements.statementlist.size();i++){
//        ui->treeDisplay->append(newprogram->lines[i].returncmdline());
//    }
    statements.runexp();//运行加载语法树
    drawexptrees();//绘制语法树
}

void MainWindow::updatecode(){
    ui->CodeDisplay->clear();//清楚代码展示部分
    for(int i=0;i<newprogram->lines.size();i++){
        ui->CodeDisplay->append(newprogram->lines[i].returncmdline());//添加代码指令
    }
}



void MainWindow::run(){
       if(trigger==true){//是否第一次刚开始加载
         ui->textBrowser->clear();
        this->newprogram->variables.clear();
        trigger=false;
       // this->statements.statementlist.clear();
        for(int i=0;i<statements.statementlist.size();i++){
            statements.statementlist[i].counttimes=0;
            statements.statementlist[i].relativecounttimes=0;
        }
        this->status=-9999;
        whetherupdate=true;
        immediate=false;
        printnumber=-2147483648;
        where=0;
        printtimes=1;
        adaptline=0;
        drawer.clear();
       }
       if(whetherupdate==false&&status==-9999){//非正常运行状态，在输入input时进行run指令
           where=0;
           whetherupdate=true;
           newprogram->variables.clear();
           run();
           return;
       }
//       if(where==0&&newprogram->variables.isEmpty()!=0){
//           where=0;
//           whetherupdate=true;
//           newprogram->variables.clear();
//           run();
//       }
        if(status==-9999){
            status=newprogram->runprogram(where,newprogram->variables,printnumber,statements);//进入program line的运行模式
        }
        if(status==-2){
            inputsomething();//加入等待输入的模式
            //run();
        }
        if(status==0){
            drawer.push_back(printnumber);//错误指令行数
            status=-9999;
            run();
        }
        if(status>0){
            adaptsomething(status);//重置
   //         run();
        }
        if(status==-4){
            handleall();
          //
            statements.statementlist[newprogram->problem_line].statementype=-4;
//            update_exptree();
            drawexptrees();//更新语法树
            return;
        }
        if(status==-5){
            handleall();
          //  ui->treeDisplay->append("jump wrong!!!");
            statements.statementlist[newprogram->problem_line].statementype=-5;
//            update_exptree();
            drawexptrees();
            return;
        }
        if(status==-10){
            handleall();
         //   ui->treeDisplay->append("Invalid commands!!!");
            statements.statementlist[newprogram->problem_line].statementype=-10;
//            update_exptree();
            drawexptrees();
            return;
        }
        if(status==-7){
            handleall();
         //   ui->treeDisplay->append("NUMBER COUNTING ERROR!!!");
            statements.statementlist[newprogram->problem_line].statementype=-7;
//            update_exptree();
            drawexptrees();
            return;
        }
        if(status==-6){
            handleall();
         //   ui->treeDisplay->append("variable wrong!!!");
            statements.statementlist[newprogram->problem_line].statementype=-6;
//            update_exptree();
            drawexptrees();
            return;
        }
    if(status==-1){//运行结束指令
        statements.runexp();
        if(successwidget->ignore==false){
            successwidget->show();
        }
        update_exptree();
        if(printtimes==1){
            ui->treeDisplay->clear();
            ui->textBrowser->clear();
            drawsomething();
            drawexptrees();
            printtimes-=1;
            trigger=1;
       }
    }
    status=-9999;
    printtimes=1;
    return;
}

void MainWindow::adaptsomething(int status){
    whetherupdate=false;
   // QString qstr=QString::fromStdString(newprogram->inputname);
  //  ui->cmdLineEdit->setText(qstr );
    ui->cmdLineEdit->setText("?");
    adaptline=status;
}

void MainWindow::drawexptrees(){

    for(int PE=0;PE<statements.statementlist.size();PE++){
        drawexptree(statements.statementlist[PE]);
    }
    return;
}

void MainWindow::drawexptree(statement tmp){
    QQueue<exp_tree*> list;
    std::string str=std::to_string(tmp.linenumber);
    std::string strnum;
    QString qstr;
    QString qstrnum;
    bool second=true;
    int count1;
    int count2;
    bool first=true;
    int num=1;
    bool firstline=1;
    switch (tmp.statementype) {
    case -4:
        str=std::to_string(tmp.linenumber);
        qstr=QString::fromStdString(str);
        ui->treeDisplay->append(qstr);
        ui->treeDisplay->append("input wrong!!!");
        return;
        break;
    case -5:
        str=std::to_string(tmp.linenumber);
        qstr=QString::fromStdString(str);
        ui->treeDisplay->append(qstr);
        ui->treeDisplay->append("jump wrong!!!");
        break;
    case -6:
        str=std::to_string(tmp.linenumber);
        qstr=QString::fromStdString(str);
        ui->treeDisplay->append(qstr);
        ui->treeDisplay->append("variable wrong!!!");
        return;
        break;
    case -7:
        str=std::to_string(tmp.linenumber);
        qstr=QString::fromStdString(str);
        ui->treeDisplay->append(qstr);
        ui->treeDisplay->append("NUMBER COUNTING ERROR!!!");
        return;
        break;
    case -10:
        str=std::to_string(tmp.linenumber);
        qstr=QString::fromStdString(str);
        ui->treeDisplay->append(qstr);
        ui->treeDisplay->append("Invalid commands!!!");
        return;
        break;
    case 1:

            str=std::to_string(tmp.linenumber);
            qstr=QString::fromStdString(str);
            ui->treeDisplay->append(qstr);
            ui->treeDisplay->insertPlainText(" LET =  ");
            count1=tmp.counttimes;
            str=std::to_string(count1);
            qstr=QString::fromStdString(str);
            ui->treeDisplay->insertPlainText("this LET statement has existed for  ");
            ui->treeDisplay->insertPlainText(qstr);
            ui->treeDisplay->insertPlainText(" times");
            list.push_back(tmp.tree1);
            while(!list.empty()){
                if(first==true){
                    exp_tree* p=list.head();
                    list.pop_front();
                    if(p->left!=NULL){
                        list.push_back(p->left);
                    }
                    if(p->right!=NULL){
                        list.push_back(p->right);
                    }
                    if(list.empty()) break;
                    first=false;
                }
                for(int j=0;j<2;j++){
                    ui->treeDisplay->append("");
                    for(int i=0;i<num;i++){
                        ui->treeDisplay->insertPlainText("    ");
                    }
                    std::string a;
                    QString b;
                    switch(list.head()->code){
                    case 4:
                           switch(list.head()->compond_type){
                           case 1: ui->treeDisplay->insertPlainText("+");
                                   break;
                           case 2: ui->treeDisplay->insertPlainText("-");
                                   break;
                           case 3: ui->treeDisplay->insertPlainText("*");
                                   break;
                           case 4: ui->treeDisplay->insertPlainText("/");
                                   break;
                           case 5: ui->treeDisplay->insertPlainText("MOD");
                                   break;
                           case 6: ui->treeDisplay->insertPlainText("**");
                                   break;
                           case 9: ui->treeDisplay->insertPlainText("=");
                                   break;
                           }
                           break;
                    case 2:
                           a=std::to_string(list.head()->const_data);
                           b=QString::fromStdString(a);
                           ui->treeDisplay->insertPlainText(b);
                           break;
                    case 3:
                           a=list.head()->name;
                           b=QString::fromStdString(a);
                           ui->treeDisplay->insertPlainText(b);
                           if(firstline==true) {
                               int numbe=0;
                               for(int i=0;i<newprogram->variables.size();i++){
                                   if(newprogram->variables[i].name.compare(a)==0){
                                       numbe=newprogram->variables[i].existtimes;
                                   }
                               }
                               a=std::to_string(numbe);
                               b=QString::fromStdString(a);
                               ui->treeDisplay->insertPlainText("  ");
                               ui->treeDisplay->insertPlainText("this Variable has been used for ");
                               ui->treeDisplay->insertPlainText(b);
                               ui->treeDisplay->insertPlainText(" times. ");
                               firstline=false;
                           }
                    }

                    exp_tree* p=list.head();
                    list.pop_front();
                    if(p->left!=NULL){
                        list.push_back(p->left);
                    }
                    if(p->right!=NULL){
                        list.push_back(p->right);
                    }

                    if(list.empty()) break;
                }
                                    num++;
            }
           return;
           break;
     case 2:
            str=std::to_string(tmp.linenumber);
            qstr=QString::fromStdString(str);
            ui->treeDisplay->append(qstr);
            ui->treeDisplay->insertPlainText(" PRINT  ");
            ui->treeDisplay->insertPlainText("this PRINT statement has existed for  ");
            count1=tmp.counttimes;
            str=std::to_string(count1);
            qstr=QString::fromStdString(str);
            ui->treeDisplay->insertPlainText(qstr);
            ui->treeDisplay->insertPlainText(" times");
            list.push_back(tmp.tree1);
            while(!list.empty()){
            for(int j=0;j<2;j++){
                ui->treeDisplay->append("");
                for(int i=0;i<num;i++){
                    ui->treeDisplay->insertPlainText("    ");
                }
                std::string a;
                QString b;
                switch(list.head()->code){
                case 4:
                       switch(list.head()->compond_type){
                       case 1: ui->treeDisplay->insertPlainText("+");
                               break;
                       case 2: ui->treeDisplay->insertPlainText("-");
                               break;
                       case 3: ui->treeDisplay->insertPlainText("*");
                               break;
                       case 4: ui->treeDisplay->insertPlainText("/");
                               break;
                       case 5: ui->treeDisplay->insertPlainText("MOD");
                               break;
                       case 6: ui->treeDisplay->insertPlainText("**");
                               break;
                       case 9: ui->treeDisplay->insertPlainText("=");
                               break;
                       }
                       break;
                case 2:
                       a=std::to_string(list.head()->const_data);
                       b=QString::fromStdString(a);
                       ui->treeDisplay->insertPlainText(b);
                       break;
                case 3:
                       a=list.head()->name;
                       b=QString::fromStdString(a);
                       ui->treeDisplay->insertPlainText(b);
                }
                exp_tree* p=list.head();
                list.pop_front();
                if(p->left!=NULL){
                    list.push_back(p->left);
                }
                if(p->right!=NULL){
                    list.push_back(p->right);
                }
                if(second==true){
                    j++;
                    second=false;
                }
                if(list.empty()) break;
            }
                                num++;
        }
        return;
        break;
    case 3:
        str=std::to_string(tmp.linenumber);
        qstr=QString::fromStdString(str);
        ui->treeDisplay->append(qstr);
        ui->treeDisplay->insertPlainText(" GOTO  ");
        ui->treeDisplay->insertPlainText("this GOTO statement has existed for  ");
        count1=tmp.counttimes;
        str=std::to_string(count1);
        qstr=QString::fromStdString(str);
        ui->treeDisplay->insertPlainText(qstr);
        ui->treeDisplay->insertPlainText(" times");
        ui->treeDisplay->append("    ");
        str=std::to_string(tmp.gotonumber);
        qstr=QString::fromStdString(str);
        ui->treeDisplay->insertPlainText(qstr);
        return;
        break;
    case 5:
        str=std::to_string(tmp.linenumber);
        qstr=QString::fromStdString(str);
        ui->treeDisplay->append(qstr);
        ui->treeDisplay->insertPlainText(" INPUT  ");
        count1=tmp.counttimes;
        str=std::to_string(count1);
        qstr=QString::fromStdString(str);
        ui->treeDisplay->insertPlainText(qstr);
        ui->treeDisplay->append("    ");
        qstr=QString::fromStdString(tmp.name);
        ui->treeDisplay->insertPlainText(qstr);
        return;
        break;
    case 6:
        str=std::to_string(tmp.linenumber);
        qstr=QString::fromStdString(str);
        ui->treeDisplay->append(qstr);
        ui->treeDisplay->insertPlainText(" REM");
        ui->treeDisplay->append("    ");
        qstr=QString::fromStdString(tmp.name);
        ui->treeDisplay->insertPlainText(qstr);
        return;
        break;
    case 7:str=std::to_string(tmp.linenumber);
        qstr=QString::fromStdString(str);
        ui->treeDisplay->append(qstr);
        ui->treeDisplay->insertPlainText(" END");
        return;
        break;
    case 4:
           str=std::to_string(tmp.linenumber);
            qstr=QString::fromStdString(str);
            ui->treeDisplay->append(qstr);
            ui->treeDisplay->insertPlainText(" IF ELSE  ");
            count1=tmp.counttimes;
            str=std::to_string(count1);
            qstr=QString::fromStdString(str);
            ui->treeDisplay->insertPlainText("this if-else statement has been used for ");
            ui->treeDisplay->insertPlainText(qstr);
            ui->treeDisplay->insertPlainText(" times and ");
            count2=tmp.relativecounttimes;
            str=std::to_string(count2);
            qstr=QString::fromStdString(str);
            ui->treeDisplay->insertPlainText(qstr);
            ui->treeDisplay->insertPlainText(" times respectively ");
            ui->treeDisplay->append("    ");
            std::string buf(1,tmp.sign);
            QString signal_1=QString::fromStdString(buf);
            ui->treeDisplay->insertPlainText(signal_1);
            list.push_back(tmp.tree1);
            while(!list.empty()){
            for(int j=0;j<2;j++){
            ui->treeDisplay->append("");
            for(int i=0;i<num;i++){
                ui->treeDisplay->insertPlainText("    ");
            }
            std::string a;
            QString b;
            switch(list.head()->code){
            case 4:
                   switch(list.head()->compond_type){
                   case 1: ui->treeDisplay->insertPlainText("+");
                           break;
                   case 2: ui->treeDisplay->insertPlainText("-");
                           break;
                   case 3: ui->treeDisplay->insertPlainText("*");
                           break;
                   case 4: ui->treeDisplay->insertPlainText("/");
                           break;
                   case 5: ui->treeDisplay->insertPlainText("MOD");
                           break;
                   case 6: ui->treeDisplay->insertPlainText("**");
                           break;
                   case 9: ui->treeDisplay->insertPlainText("=");
                           break;
                   }
                   break;
            case 2:
                   a=std::to_string(list.head()->const_data);
                   b=QString::fromStdString(a);
                   ui->treeDisplay->insertPlainText(b);
                   break;
            case 3:
                   a=list.head()->name;
                   b=QString::fromStdString(a);
                   ui->treeDisplay->insertPlainText(b);
            }
            exp_tree* p=list.head();
            list.pop_front();
            if(p->left!=NULL){
                list.push_back(p->left);
            }
            if(p->right!=NULL){
                list.push_back(p->right);
            }
            if(list.empty()) break;
            }
                            num++;
        }
        num=1;
        list.push_back(tmp.tree2);
        while(!list.empty()){
        for(int j=0;j<2;j++){
        ui->treeDisplay->append("");
        for(int i=0;i<num;i++){
            ui->treeDisplay->insertPlainText("    ");
        }
        std::string a;
        QString b;
        switch(list.head()->code){
        case 4:
               switch(list.head()->compond_type){
               case 1: ui->treeDisplay->insertPlainText("+");
                       break;
               case 2: ui->treeDisplay->insertPlainText("-");
                       break;
               case 3: ui->treeDisplay->insertPlainText("*");
                       break;
               case 4: ui->treeDisplay->insertPlainText("/");
                       break;
               case 5: ui->treeDisplay->insertPlainText("MOD");
                       break;
               case 6: ui->treeDisplay->insertPlainText("**");
                       break;
               case 9: ui->treeDisplay->insertPlainText("=");
                       break;
               }
               break;
        case 2:
               a=std::to_string(list.head()->const_data);
               b=QString::fromStdString(a);
               ui->treeDisplay->insertPlainText(b);
               break;
        case 3:
               a=list.head()->name;
               b=QString::fromStdString(a);
               ui->treeDisplay->insertPlainText(b);
        }
        exp_tree* p=list.head();
        list.pop_front();
        if(p->left!=NULL){
            list.push_back(p->left);
        }
        if(p->right!=NULL){
            list.push_back(p->right);
        }
        if(list.empty()) break;
        }
                        num++;
        }
        strnum=std::to_string(tmp.gotonumber);
        qstrnum=QString::fromStdString(strnum);
        ui->treeDisplay->append("    ");
        ui->treeDisplay->insertPlainText(qstrnum);
        return;
        break;
   }
}

void MainWindow::drawsomething(){
    ui->textBrowser->clear();
    for(int i=0;i<drawer.size();i++){
        std::string str=std::to_string(drawer[i]);
        QString qstr=QString::fromStdString(str);
        ui->textBrowser->append(qstr);
    }
    return;
}

void MainWindow::exiting(){
    qApp->exit(0);//退出程序
}

void MainWindow::inputsomething(){
    whetherupdate=false;//输入状态
   // QString qstr=QString::fromStdString(newprogram->inputname);
  //  ui->cmdLineEdit->setText(qstr);
    ui->cmdLineEdit->setText("?");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_cmdLineEdit_editingFinished()
{
    bool respond =false;
    QString cmd = ui->cmdLineEdit->text();
    ui->cmdLineEdit->setText("");
    if(cmd.length()!=0&&whetherupdate==true){
        if(cmd[0].isDigit()!=0){
                newprogram->addprogram(cmd);
                statements.addstatement(cmd);
        }
        else   respond=true;
    }
    if(cmd.length()!=0&&whetherupdate==true){
        this->updatecode();
        this->update_exptree();
    }
    if(whetherupdate==false){
        std::string cmdd=cmd.toStdString();
        int j=0;
        for(j=0;j<int(cmdd.length());j++){
            if(isdigit(cmdd[j])==0&&isdigit(cmdd[j+1])!=0){
                break;
            }
        }
        if(j==int(cmdd.length())){
            ui->treeDisplay->append("  input error  ");
            inputsomething();
            return;
        }
        std::string numb(cmdd.begin()+1,cmdd.end());
        for(int new1=0;new1<int(numb.size());new1++){
            if(isdigit(numb[new1])==0&&(numb[new1]!='-')&&(numb[new1]!=' ')){
                ui->treeDisplay->append("  input error  ");//输入input错误
                inputsomething();
                return;
            }
        }
        int num=atoi(numb.c_str());
        if(adaptline==0){
            expression& backer=newprogram->variables.back();
            backer.data=num;
            adaptline=0;
        }
        else{
            expression& elser=newprogram->variables[adaptline-1];
            elser.data=num;
            adaptline=0;
        }
        whetherupdate=true;
        if(immediate==false){
            status=-9999;
           run();
        }
        else{immediate=false;}
    }
    if(respond==true){
        immediate_respond(cmd);
        respond=false;
    }
}

void MainWindow::immediate_respond(QString cmdd){//快速回答,当不存在行数时
     int i=0;
     std::string cmd=cmdd.toStdString();
     for(i=0;i<int(cmd.length());i++){
          if(cmd[i]!=' '&&cmd[i+1]==' '){
              break;
          }
     }
     if(i==int(cmd.length())){
           if(cmd.compare("RUN")==0){run();}
           else if(cmd.compare("CLEAR")==0){clearall();}//clear case
           else if(cmd.compare("QUIT")==0){exiting();}//quit case
           else if(cmd.compare("LOAD")==0){loadprogram();}///load case
           else if(cmd.compare("HELP")==0){I_NEED_HELP();}//help case
           else if(cmd.compare("LIST")==0){}
           else{
               ui->treeDisplay->append("Invalid commands!!!");//wrong case
               return;
           }

     }
     else{
          std::string tmp(cmd.begin(),cmd.begin()+i+1);
          for(i=0;i<int(cmd.length());i++){
              if(cmd[i]==' '&&cmd[i+1]!=' '){
                  break;
              }
          }
          if(tmp.compare("LET")==0){//let case
              std::string tmpp(cmd.begin()+i+1,cmd.end());
              expressions tmp;
              tmp.iflet=true;
              int a;
              if(isdigit(tmpp[0])!=0||isalpha(tmpp[0])==false){
                  ui->treeDisplay->append("quick respond input wrong!!!");//wrong case
                  return;
              }
              int i_2=0;
              for(i_2=0;i_2<int(tmpp.length());i_2++){
                  if(tmpp[i_2]=='='&&tmpp[i_2+1]!='='){
                      break;
                  }
              }
              if(i_2==int(tmpp.length())){
                  ui->treeDisplay->append("quick respond input wrong!!!");
                  return;
              }
              tmp.addexpression(tmpp,newprogram->variables,a,true,true);
              if(tmp.wrong==true){
                  ui->treeDisplay->append("quick respond input wrong!!!");
                  return;
              }
              if(tmp.variablewrong==true){
                  ui->treeDisplay->append("quick respond variable wrong!!!");
                  return;
              }
              if(tmp.numwrong==true){
                  ui->treeDisplay->clear();
                  ui->treeDisplay->append("quick respond number counting wrong!!!");
                  return;
              }
          }
          else if(tmp.compare("INPUT")==0){
              std::string tmpp(cmd.begin()+i+1,cmd.end());
              if(isalpha(tmpp[0])==false) {
                   ui->treeDisplay->append("quick respond input wrong!!!");
                   return;
              }
              int i=0;
              for(i=0;i<newprogram->variables.size();i++){
                  if(newprogram->variables[i].name==tmpp){
                      break;
                  }

              }
              if(i==newprogram->variables.size()){
                  expression st;
                  st.name=tmpp;
                  newprogram->variables.push_back(st);
                  immediate=true;
                  st.existed=true;
                  inputsomething();
              }
              else{
                  immediate=true;
                  adaptsomething(i);
              }
          }
          else if(tmp.compare("PRINT")==0){
              std::string tmpp(cmd.begin()+i+1,cmd.end());
              if((isdigit(tmpp[0])==0&&isalpha(tmpp[0])==false&&tmpp[0]!='_')&&!(tmpp[0]=='-'&&isdigit(tmpp[1])!=0)&&tmpp[0]!='('){
                  ui->treeDisplay->append("quick respond input wrong!!!");
                  return;
              }
              expressions tmp;
              int a;
              tmp.addexpression(tmpp,newprogram->variables,a,false,true);
              if(tmp.wrong==true){
                  ui->treeDisplay->append("quick respond input wrong!!!");
                  return;
              }
              if(tmp.variablewrong==true){
                  ui->treeDisplay->append("quick respond variable wrong!!!");
                  return;
              }
              if(tmp.numwrong==true){
                  ui->treeDisplay->append("quick respond number counting wrong!!!");
                  return;
              }

              std::string str=std::to_string(a);
              QString qstr=QString::fromStdString(str);
              ui->textBrowser->append(qstr);
          }
          else{
          ui->treeDisplay->append("Invalid command!!!");
          return;
          }
     }
}

void MainWindow::handleall(){
    ui->treeDisplay->clear();
//    ui->textBrowser->clear();
//    for(int i=0;i<newprogram->lines.size();i++){
//        if(newprogram->problem_line==newprogram->lines[i].getlinenumber()){
//            newprogram->lines.erase(newprogram->lines.begin()+i);
//            break;
//        }
//    }
//    for(int i=0;i<statements.statementlist.size();i++){
//        if(newprogram->problem_line==statements.statementlist[i].linenumber){
//            statements.statementlist.erase(statements.statementlist.begin()+i);
//        }
//    }
   for(int i=0;i<statements.statementlist.size();i++){
       statements.statementlist[i].counttimes=0;
   }
    this->newprogram->variables.clear();
    this->status=-9999;
    whetherupdate=true;
    immediate=false;
    printnumber=-2147483648;
    where=0;
    drawer.clear();
    ui->textBrowser->append("error");
    printtimes=1;
    adaptline=0;
    trigger=0;
//    int i=newprogram->lines[newprogram->problem_line].getlinenumber();
//    std::string str=std::to_string(i);
//    QString qstr=QString::fromStdString(str);
//    ui->treeDisplay->append("LINE  ");
//    ui->treeDisplay->insertPlainText(qstr);
    return;
}


void MainWindow::clearall(){
    ui->treeDisplay->clear();
    ui->textBrowser->clear();
    ui->CodeDisplay->clear();
    this->newprogram->variables.clear();
    this->newprogram->lines.clear();
//    this->newprogram->programend=false;
    this->statements.statementlist.clear();
    this->status=-9999;
    drawer.clear();
    whetherupdate=true;
    immediate=false;
    printnumber=-2147483648;
    where=0;
    printtimes=1;
    adaptline=0;
    trigger=0;
    ui->treeDisplay->append("Please type HELP in the program input box below, if you have any questions. Good Luck! ( Tips: you can ignore this sentence, it will be deleted when the program runs )");
    return;

}

void MainWindow::loadprogram(){//load 函数
    QString fileName = QFileDialog::getOpenFileName(
                        this,
                        tr("open a file."),
                        "",
                        tr("text(*.txt);;bas(*.bas);;"));//判断是否是txt文件,只打开txt文件

            if (fileName.isEmpty())
            {
                wrongfile *widgit=new wrongfile;
                widgit->show();
                return;
            }
            else
            {
                QFile file(fileName);
                //打开文件
                if(!file.open(QIODevice::ReadOnly | QIODevice::Text))//只读text
                {
                    wrongfile *widgit=new wrongfile;
                    widgit->show();
                    return;
                }
         while (!file.atEnd())//读取到文档结尾
         {
             QByteArray line = file.readLine();
             QString str(line);
             str =str.trimmed();
             newprogram->addprogram(str);
             statements.addstatement(str);
         }
         timer->start(100);
         updatecode();
         update_exptree();
         return;
    }
}

void MainWindow::I_NEED_HELP(){
    HELP* helpwindow=new HELP;
    helpwindow->show();
}
