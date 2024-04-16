#ifndef EXP_TREE_H
#define EXP_TREE_H
#include <string>
#include <variable.h>
#include <stack>
#include <QVector>
#include "expression_tree.h"
#include "statement.h"


class exp_tree
{

public:
    exp_tree(){};//语法树
    int compond_type;
    exp_tree* right=nullptr;
    exp_tree* left=nullptr;
    int code;
    int type;
    int importance;
    int const_data;
    int data;
    bool existed=0;
    std::string name;

    int existtimes=0;//出现次数
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

class exp_trees
{
   private:

    QVector<exp_tree> expression_list;
    QVector<exp_tree> term_list;
    QVector<exp_tree> operation_list;
 //   expression_tree exp_tree;
    std::stack<exp_tree> term_stack;
    std::stack<exp_tree> operation_stack;
    std::stack<exp_tree> counting_stack;
    bool ifadapt;
    bool ifnegative=1;
    int ifdone=0;
    bool iftop=1;
   public:
    bool numwrong=false;
    bool variablewrong=false;
    bool wrong=false;
    exp_trees(){};
    exp_tree* buffer;
    //void
    bool iflet=false;
    bool equalsignal=true;
    int equaltimes=0;
    void checkequal();
    void addexpression(std::string);
    void handleexpression();
    void checktype(std::string tmp);
    int whetheroperation(std::string tmp);
    void pushoperation(exp_tree tmp);
    void addtree(exp_tree tmp);
    void termpush(exp_tree tmp);
    void autoaddingtree();
    void countingnum(exp_tree *node);
    void handlecounting(int type);
};


#endif // EXP_TREE_H
