#ifndef STATEMENT_H
#include <QApplication>
#define STATEMENT_H
#include <string>
#include <variable.h>
#include <stack>
#include <QVector>
#include "expression_tree.h"
#include <expression.h>
#include "expression.h"
#include <exp_tree.h>
//class expression;
class exp_tree;
class statement
{
public:
    int statementype;
    exp_tree* tree1=nullptr;
    exp_tree* tree2=nullptr;
    std::string commands;
    int counttimes=0;
    statement();
    int relativecounttimes=0;
    int variablecounttimes=0;
    int linenumber;
    int gotonumber;
    char sign;
    std::string name;
    bool err=false;
    statement(int a,std::string b){
        linenumber=a;
        commands=b;
    }
    void changetmp(std::string tm){
        commands=tm;
    }
    void afterrun();
};

class statements{
public: QVector<statement> statementlist;
    void addstatement(QString cmd);
    void runexp();
private:
};

#endif // STATEMENT_H
