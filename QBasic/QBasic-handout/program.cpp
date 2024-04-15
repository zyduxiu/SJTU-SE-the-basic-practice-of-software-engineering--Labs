#include "program.h"
#include <QString>
#include <string>
#include <QVector>
#include "mainwindow.h"
#include "program_line.h"
#include <qvector.h>
program::program()
{

}

int program::runprogram(int& whichline,QVector<expression>& variables,int &printnumber,statements & statements){
    int linenum=-9999;int i=0;
    if(whichline==-1){
     //   programend=true;
        return -1;}
    for(i=0;i<lines.size();i++){
        if(whichline==i){
            linenum=lines[i].runline(variables,printnumber,statements.statementlist[i]);
            break;
        }
    }
    if(i==lines.size()){
      //  programend=true;
        return -1;
    }
    if(linenum==-9999){
        whichline+=1;
    }
    if(linenum==-2){
        whichline+=1;
        return 0;
    }
    if(linenum==-3){
        whichline+=1;
        rem=lines[i].remline;
    }
    if(linenum==-100) {
        //inputname=lines[i].name;
        whichline+=1;
        return -2;
    }
    if(linenum<-100&&linenum>-200) {
        whichline+=1;
        return -100-linenum;
    }
    if(linenum>=0){
        int i=0;
        for(i=0;i<lines.size();i++){
            if(linenum==lines[i].getlinenumber()){
                whichline=i;
                break;
            }
        }
        if(i==lines.size()){
         //   programend=true;
            return -1;
        }
    }
    if(linenum==-1)       //  programend=true;
        return -1;
    runprogram(whichline,variables,printnumber,statements);
}

void program::addprogram(QString cmd){
    int i=0;int j=0;
    for(i=0;i<cmd.length();i++){
        if(cmd[i]!=' '&&cmd[i+1]==' '){
            break;
        }
    }
    std::string cmd2=cmd.toStdString();
    std::string tmp(cmd2.begin(),cmd2.begin()+i+1);
    int num=atoi(tmp.c_str());
    if(i==cmd.length()){
        if(lines.size()!=0){
            for(j=0;j<lines.size();j++){
                if(num<lines[j].getlinenumber()){
                     break;
                }
                if(num==lines[j].getlinenumber()){
                    lines.erase(lines.begin()+j);
                    return;
                }
            }
            return;
        }
    else{
        return;
        }
    }
    for(i=0;i<cmd.length();i++){
        if(cmd[i]==' '&&cmd[i+1]!=' '){
            break;
        }
    }
    std::string tmp2(cmd2.begin()+i+1,cmd2.end());
    if(lines.size()!=0){
        for(j=0;j<lines.size();j++){
            if(num<lines[j].getlinenumber()){
                break;
            }
            if(num==lines[j].getlinenumber()){
                if(tmp2.size()!=0){
                    lines[j].changecmd(tmp2);
                }
                else lines.erase(lines.begin()+j);
                return;
            }
        }
        if(j!=lines.size()){
            program_line tmpp(num,tmp2);
            lines.insert(lines.begin()+j,tmpp);
            return;
        }
        else{
            if(tmp2.size()!=0){
                program_line tmpp(num,tmp2);
                lines.push_back(tmpp);
                return;
            }
            return;
        }
    }
    else{
        if(tmp2.size()!=0){
            program_line tmpp(num,tmp2);
            lines.push_back(tmpp);
            return;
        }
        return;
    }

}
