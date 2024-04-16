#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <string>
#include <variable.h>
#include <stack>
#include <QVector>
#include "expression_tree.h"
#include "statement.h"
class expression
{
private:


public:
    expression();
    int compond_type;
    expression* right=NULL;
    expression* left=NULL;
    int code;
    int type;
    int importance;
    int const_data;
    int data;
    bool existed=0;
    std::string name;

    int existtimes=0;
};

//class signal_exp:public expression{
//public:
//    int type;
//    int code=1;
//    int importance;
//    signal_exp(){};
//};

//class const_exp:public expression
//{
//public:
//    int data;
//    int code=2;
//    const_exp(){};
//};

//class compond_exp:public expression
//{
//private:
//    expression operate;
//    compond_exp(){};
//public:
//    int code=4;
//    expression *left;
//    expression *right;
//};

//class variable:public expression
//{
//public:
//    int code=3;
//    variable();
//    std::string name;
//    int data;
//};

class expressions
{
   private:

    QVector<expression> expression_list;
    QVector<expression> term_list;
    QVector<expression> operation_list;
 //   expression_tree exp_tree;
    std::stack<expression> term_stack;
    std::stack<expression> operation_stack;
    std::stack<expression> counting_stack;
    bool ifadapt;
    bool ifnegative=1;
    int ifdone=0;
    bool iftop=1;
   public:
    bool numwrong=false;
    bool variablewrong=false;
    bool wrong=false;
    expressions(){};
     expression* buffer;
    //void
    bool iflet=false;
    bool equalsignal=true;
    int equaltimes=0;
    void checkequal();
    void addexpression(std::string,QVector<expression>& variables,int &a,bool ifadjust,bool ifexp);
    void handleexpression(QVector<expression>& variables,bool ifadjust);
    void checktype(std::string tmp,QVector<expression>& variables,bool ifexp);
    int whetheroperation(std::string tmp);
    void pushoperation(expression tmp);
    void addtree(expression tmp);
    void termpush(expression tmp,QVector<expression>& variables);
    void autoaddingtree();
    void countingnum(expression *node);
    void handlecounting(int type);
};


#endif // EXPRESSION_H
