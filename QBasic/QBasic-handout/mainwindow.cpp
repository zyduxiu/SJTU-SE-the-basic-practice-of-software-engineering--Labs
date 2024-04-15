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
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer->start(100);
    connect(ui->btnClearCode,SIGNAL(clicked()),this,SLOT(clearall()));
    connect(ui->cmdLineEdit,SIGNAL(returnPressed()),this,SLOT(returnpressed()));
    connect(ui->btnLoadCode,SIGNAL(clicked()),this,SLOT(returnpressed()));
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::repaint));
    connect(ui->btnRunCode,SIGNAL(clicked()),this,SLOT(run()));
    connect(ui->btnLoadCode,SIGNAL(clicked()),this,SLOT(loadprogram()));
}

void MainWindow::updatecode(){
    ui->CodeDisplay->clear();
    for(int i=0;i<newprogram->lines.size();i++){
        ui->CodeDisplay->append(newprogram->lines[i].returncmdline());
    }
}

void MainWindow::run(){
        if(status==-9999){
            status=newprogram->runprogram(where,newprogram->variables,printnumber,statements);
        }
        if(status==-2){
            inputsomething();
            //run();
        }
        if(status==0){
            drawsomething(printnumber);
            status=-9999;
         //   run();
        }
        if(status>0){
            adaptsomething(status);
   //         run();
        }
    if(status==-1){
        statements.runexp(newprogram->variables);
        if(printtimes==1){
            ui->treeDisplay->clear();
            drawexptrees();
            printtimes-=1;
       }
    }
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
    QQueue<expression*> list;
    std::string str=std::to_string(tmp.linenumber);
    std::string strnum;
    QString qstr;
    QString qstrnum;
    int count1;
    int count2;
    bool first=true;
    int num=1;
    bool firstline=1;
    switch (tmp.statementype) {
    case 1:

            str=std::to_string(tmp.linenumber);
            qstr=QString::fromStdString(str);
            ui->treeDisplay->append(qstr);
            ui->treeDisplay->insertPlainText(" LET =  ");
            count1=tmp.counttimes;
            str=std::to_string(count1);
            qstr=QString::fromStdString(str);
            ui->treeDisplay->insertPlainText(qstr);
            list.push_back(tmp.tree1);
            while(!list.empty()){
                if(first==true){
                    expression* p=list.head();
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
                               ui->treeDisplay->insertPlainText(b);
                               firstline=false;
                           }
                    }

                    expression* p=list.head();
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
            count1=tmp.counttimes;
            str=std::to_string(count1);
            qstr=QString::fromStdString(str);
            ui->treeDisplay->insertPlainText(qstr);
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
                expression* p=list.head();
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
    case 3:
        str=std::to_string(tmp.linenumber);
        qstr=QString::fromStdString(str);
        ui->treeDisplay->append(qstr);
        ui->treeDisplay->insertPlainText(" GOTO  ");
        count1=tmp.counttimes;
        str=std::to_string(count1);
        qstr=QString::fromStdString(str);
        ui->treeDisplay->insertPlainText(qstr);
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
            ui->treeDisplay->insertPlainText(qstr);
            ui->treeDisplay->insertPlainText("  ");
            count2=tmp.relativecounttimes;
            str=std::to_string(count2);
            qstr=QString::fromStdString(str);
            ui->treeDisplay->insertPlainText(qstr);
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
            expression* p=list.head();
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
        expression* p=list.head();
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

void MainWindow::drawsomething(int num){
    std::string str=std::to_string(num);
    if(num==-2147483648) return;
    QString qstr=QString::fromStdString(str);
    ui->textBrowser->append(qstr);
    status=-9999;
    run();
    return;
}

void MainWindow::exiting(){
    qApp->exit(0);
}

void MainWindow::inputsomething(){
    whetherupdate=false;
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
            respond=true;
    }
    if(cmd.length()!=0&&whetherupdate==true){
        this->updatecode();
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
            return;
        }
        std::string numb(cmdd.begin()+1,cmdd.end());
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

void MainWindow::immediate_respond(QString cmdd){
     int i=0;
     std::string cmd=cmdd.toStdString();
     for(i=0;i<cmd.length();i++){
          if(cmd[i]!=' '&&cmd[i+1]==' '){
              break;
          }
     }
     if(i==cmd.length()){
           if(cmd.compare("RUN")==0){run();}
           if(cmd.compare("CLEAR")==0){clearall();}
           if(cmd.compare("QUIT")==0){exiting();}
           if(cmd.compare("LOAD")==0){loadprogram();}
           if(cmd.compare("HELP")==0){I_NEED_HELP();}
     }
     else{
          std::string tmp(cmd.begin(),cmd.begin()+i+1);
          for(i=0;i<cmd.length();i++){
              if(cmd[i]==' '&&cmd[i+1]!=' '){
                  break;
              }
          }
          if(tmp.compare("LET")==0){
              std::string tmpp(cmd.begin()+i+1,cmd.end());
              expressions tmp;
              int a;
              tmp.addexpression(tmpp,newprogram->variables,a,true,true);
          }
          if(tmp.compare("INPUT")==0){
              std::string tmpp(cmd.begin()+i+1,cmd.end());
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
          if(tmp.compare("PRINT")==0){
              std::string tmpp(cmd.begin()+i+1,cmd.end());
              expressions tmp;
              int a;
              tmp.addexpression(tmpp,newprogram->variables,a,false,true);
              std::string str=std::to_string(a);
              QString qstr=QString::fromStdString(str);
              ui->textBrowser->append(qstr);
          }
     }
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
    whetherupdate=true;
    immediate=false;
    printnumber=-2147483648;
    where=0;
    printtimes=1;
    adaptline=0;
    return;
}

void MainWindow::loadprogram(){
    clearall();
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()){
         QFile file(fileName);
         file.open(QIODevice::Truncate | QIODevice::ReadOnly);
         while (!file.atEnd())
         {
             QByteArray line = file.readLine();
             QString str(line);
             str =str.trimmed();
             newprogram->addprogram(str);
             statements.addstatement(str);
         }
         timer->start(100);
         updatecode();
         return;
    }
}

void MainWindow::I_NEED_HELP(){
    HELP* helpwindow=new HELP;
    helpwindow->show();
}
