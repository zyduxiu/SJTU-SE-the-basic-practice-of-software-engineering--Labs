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
            linenum=lines[i].runline(variables,printnumber,statements.statementlist[i]);//下一行状态
            break;
        }
    }
    if(i==lines.size()){
      //  programend=true;
        return -1;
    }
    if(linenum==-9999){//正常执行状态
        whichline+=1;
    }
    if(linenum==-2){//输入状态
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
    if(linenum==-7){
        problem_line=whichline;
        return -7;
    }
    if(linenum==-10){
        problem_line=whichline;
        return -10;
    }
    if(linenum<-100&&linenum>-200) {
        whichline+=1;//跳转错误
        return -100-linenum;
    }
    if(linenum==-4){
        problem_line=whichline;
        return -4;}//命名错误!!!
    if(linenum==-6) {
        problem_line=whichline;
        return -6;
    }//非法状态
    if(linenum>=0){//跳转状态
        int i=0;
        for(i=0;i<lines.size();i++){
            if(linenum==lines[i].getlinenumber()){
                whichline=i;
                break;
            }
        }
        if(i==lines.size()){//无法找到跳转位置！！
            problem_line=whichline;
            return -5;
        }
    }
    if(linenum==-1)       //  programend=true;
        return -1;
    runprogram(whichline,variables,printnumber,statements);//递归部分，执行下一条指令
}

void program::addprogram(QString cmd){
    int i=0;int j=0;
    for(i=0;i<cmd.length();i++){
        if(cmd[i]!=' '&&cmd[i+1]==' '){
            break;
        }
    }
    std::string cmd2=cmd.toStdString();
    std::string tmp(cmd2.begin(),cmd2.begin()+i+1);//截取字符串
    int num=atoi(tmp.c_str());
    if(i==cmd.length()){//空指令，表示删除
        if(lines.size()!=0){//lines指令集不为空
            for(j=0;j<lines.size();j++){
                if(num<lines[j].getlinenumber()){
                     break;
                }
                if(num==lines[j].getlinenumber()){
                    lines.erase(lines.begin()+j);//删除指令
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
    std::string tmp2(cmd2.begin()+i+1,cmd2.end());//截取字符串
    if(lines.size()!=0){
        for(j=0;j<lines.size();j++){
            if(num<lines[j].getlinenumber()){
                break;
            }
            if(num==lines[j].getlinenumber()){
                if(tmp2.size()!=0){
                    lines[j].changecmd(tmp2);//更改指令
                }
                else lines.erase(lines.begin()+j);
                return;
            }
        }
        if(j!=lines.size()){
            program_line tmpp(num,tmp2);
            lines.insert(lines.begin()+j,tmpp);//插入指令在合适位置
            return;
        }
        else{
            if(tmp2.size()!=0){
                program_line tmpp(num,tmp2);
                lines.push_back(tmpp);//增加指令到最后
                return;
            }
            return;
        }
    }
    else{
        if(tmp2.size()!=0){
            program_line tmpp(num,tmp2);
            lines.push_back(tmpp);//指令集为空，直接添加指令到最后
            return;
        }
        return;
    }

}
