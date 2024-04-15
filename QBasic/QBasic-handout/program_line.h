#ifndef PROGRAM_LINE_H
#define PROGRAM_LINE_H
#include "command.h"
#include <string>
#include <QVector>
#include "expression.h"
#include "statement.h"
class program_line
{
private:
    std::string commands;
    int linenumber;
public:
    std::string remline;
    command *thiscommand=new command;
    program_line();
    program_line(int a,std::string b){
        linenumber=a;
        commands=b;
    }
    int runline(QVector<expression>& variables,int &printnumber,statement& statement);
    int getlinenumber(){
        return linenumber;
    }
    std::string getcommands(){
        return commands;
    }
    QString returncmdline();
    void changecmd(std::string cmd);
    std::string eliminatespace(std::string cmd);
    bool comparing(int a,char b,int c);
    std::string name;
};

#endif // PROGRAM_LINE_H
