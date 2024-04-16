#ifndef PROGRAM_H
#define PROGRAM_H
#include "program_line.h"
#include <QVector>
#include <qvector.h>
#include <QString>
#include "command.h"
#include "expression.h"
#include "statement.h"
#include "statement_tree.h"
class program
{
private:

public:
    command *nextcommand=new command;
    program();
    void addprogram(QString cmd);
    QVector<program_line> lines;
    QVector<expression> variables;
    int runprogram(int& whichline,QVector<expression>& variables,int &printnumber,statements & statements);
    std::string rem;
    int problem_line=-1;
  //  std::string inputname;
 //   bool programend=false;
};

#endif // PROGRAM_H
