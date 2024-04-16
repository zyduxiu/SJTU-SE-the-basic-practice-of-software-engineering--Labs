#include "program_line.h"
#include <QVector>
#include <qvector.h>
#include <string.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
program_line::program_line()
{

}

//std::string program_line::eliminatespace(std::string cmd){//自动消除空格符的函数
  //  int i=0;int j=0;
 //   char* cmdd;
   // std::string desti;
   // for(i=0;i<int(cmd.length());i++){
    //    if(cmd[i]!=' '){
          //  cmdd[j++]=cmd[i];
      //  }
   // }
    //cmdd[j]='\0';
//    desti=cmdd;
  //  return desti;
//}

int program_line::runline(QVector<expression>& variables,int &printnumber,statement & statement){//执行program line
    int i=0;
    for(i=0;i<int(commands.length());i++){
        if(commands[i]!=' '&&commands[i+1]==' '){
            break;
        }
    }
    if(i!=int(commands.length())){
            std::string type(commands.begin(),commands.begin()+i+1);
            if(type.compare("REM")==0){
                int i_1=0;
                for(i_1=0;i_1<int(commands.length());i_1++){
                    if(commands[i_1]==' '&&commands[i_1+1]!=' '){
                        break;
                    }
                }
                std::string next(commands.begin()+i_1+1,commands.end());
                remline=next;
                return -3;
            }
            if(type.compare("LET")==0){//LET case
                thiscommand->getcommandtype(1);
                int i_1=0;
                for(i_1=0;i_1<int(commands.length());i_1++){
                    if(commands[i_1]==' '&&commands[i_1+1]!=' '){
                        break;
                    }
                }
                if(i_1==int(commands.length())){
                    return -4;//wrong case
                }
                std::string next(commands.begin()+i_1+1,commands.end());
                if(isdigit(next[0])!=0||isalpha(next[0])==false){return -4;}//wrong case
                int i_2=0;
                for(i_2=0;i_2<int(next.length());i_2++){
                    if(next[i_2]=='='&&next[i_2+1]!='='){
                        break;
                    }
                }
                if(i_2==int(next.length())){return -4;}//wrong case
                expressions tmp;
                tmp.iflet=true;
                int useless;
                tmp.addexpression(next,variables,useless,true,false);
                if(tmp.wrong==true||tmp.equalsignal==false){
                    return -4;
                }
                if(tmp.variablewrong==true){
                    return -6;
                }
                if(tmp.numwrong==true){
                    return -7;
                }

//                std::string variable_name(next.begin(),next.begin()+i_1+1);
//                std::string nextt(next.begin()+i_1+2,next.end());
//                int i_2;
//                for(i_2=0;i_2<nextt.length();i_2++){
//                    if(nextt[i_2]!=' '&&nextt[i_2+1]==' '){
//                        break;
//                    }
//                }
//                if(i_2==nextt.length()){return -1;}
//                std::string equal(nextt.begin(),nextt.begin()+i_2+1);
//                if(equal.compare("=")!=0){return -1;}
//                std::string last(nextt.begin()+i_2+2,nextt.end());
//                if(last.length()==0){return -1;}
//                int number=atoi(last.c_str());
//                if(variables.size()==0){
//                    variable tmp;
//                    tmp.name=variable_name;
//                    tmp.data=number;
//                    variables.push_back(tmp);
//                    return -9999;
//                }
//                else{
//                    int j=0;
//                    for(j=0;j<variables.size();j++){
//                        if(variables[j].name.compare(variable_name)==0){
//                            variables[j].data=number;
//                            break;
//                        }
//                    }
//                    if(j==variables.size()){
//                        variable tmp;
//                        tmp.name=variable_name;
//                        tmp.data=number;
//                        variables.push_back(tmp);
//                    }
//                    return -9999;
//                }
                statement.counttimes+=1;//指令出现次数+1
                return -9999;
            }
            if(type.compare("INPUT")==0){//INPUT CASE
                int i_1=0;
                thiscommand->getcommandtype(2);
                for(i_1=0;i_1<int(commands.length());i_1++){
                    if(commands[i_1]==' '&&commands[i_1+1]!=' '){
                        break;
                    }
                }
                if(i_1==int(commands.length())){
                    return -4;
                }
                else{
                    statement.counttimes+=1;//counttime+=1；
                    std::string next(commands.begin()+i_1+1,commands.end());
                    if(isalpha(next[0])==false) {
                        return -4;
                    }
                    for(int i=0;i<int(next.size());i++){
                        if(isalpha(next[i])==false&&isdigit(next[i])==0&&next[i]!='_'){
                            return -4;
                        }
                    }
                    int i_2=0;
                    for(i_2=0;i_2<variables.size();i_2++){
                        if(variables[i_2].name.compare(next)==0){
                            break;
                        }
                    }
                    name=next;
                    if(i_2==variables.size()){
                        expression tmp;
                        tmp.name=next;
                        tmp.existed=true;
                        variables.push_back(tmp);
                        return -100;
                    }
                    return -101-i_2;
                }
            }
            if(type.compare("PRINT")==0){//print case
                int i_1=0;
                thiscommand->getcommandtype(2);
                for(i_1=0;i_1<int(commands.length());i_1++){
                    if(commands[i_1]==' '&&commands[i_1+1]!=' '){
                        break;
                    }
                }
                if(i_1==int(commands.length())){
                    return -4;
                }
                else{
                    statement.counttimes+=1;
                    std::string next(commands.begin()+i_1+1,commands.end());
                    int a;
                    if(isdigit(next[0])==0&&isalpha(next[0])==false&&(next[0]!='-')&&(next[0]!='(')) return -4;//WRONG CASE
                    expressions tmp;
                    tmp.addexpression(next,variables,a,false,false);//handle expression
                    if(tmp.wrong==true||tmp.equalsignal==false){
                        return -4;
                    }
                    if(tmp.variablewrong==true){
                        return -6;
                    }
                    if(tmp.numwrong==true){
                        return -7;
                    }
                    printnumber=a;
                    return -2;//print something ，return print status
                    }

               }
           if(type.compare("GOTO")==0){
               int i_1=0;
               thiscommand->getcommandtype(2);
               for(i_1=0;i_1<int(commands.length());i_1++){
                   if(commands[i_1]==' '&&commands[i_1+1]!=' '){
                       break;
                   }
               }
               if(i_1==int(commands.length())){
                   return -4;
               }
               else{
                   statement.counttimes+=1;//exist time++
                   std::string next(commands.begin()+i_1+1,commands.end());
                   for(int i=0;i<int(next.size());i++){
                       if(isdigit(next[i])==0){
                           return -4;//wrong case
                       }
                   }
                   int linenum=atoi(next.c_str());
                   if(linenum>=0){
                       return linenum;
                   }
               return -1;
               }
           }
           if(type.compare("IF")==0){//IF case
                int i_1=0;
                for(i_1=0;i_1<int(commands.length());i_1++){
                    if(commands[i_1]==' '&&commands[i_1+1]!=' '){
                        break;
                    }
                }
                if(i_1==int(commands.length())){
                    return -4;
                }
                int i_2=0;
                for(i_2=i_1;i_2<int(commands.length());i_2++){//截取字符串
                    if(commands[i_2]!=' '&&commands[i_2+1]==' ') break;
                    if(commands[i_2]!='>'&&commands[i_2+1]=='>') break;
                    if(commands[i_2]!='<'&&commands[i_2+1]=='<') break;
                    if(commands[i_2]!='='&&commands[i_2+1]=='=') break;
                }
                if(i_2==int(commands.length())){
                    return -4;
                }
                std::string cd(commands.begin()+i_1+1,commands.begin()+i_2+1);
                int a=0;
                expressions tmp;
                tmp.addexpression(cd,variables,a,false,false);
                if(tmp.wrong==true||tmp.equalsignal==false){
                    return -4;
                }
                if(tmp.variablewrong==true){
                    return -6;
                }
                if(tmp.numwrong==true){
                    return -7;
                }
                int i_3=0;
                for(i_3=i_2;i_3<int(commands.length());i_3++){
                    if(commands[i_3]!='>'&&commands[i_3+1]=='>') break;//判断中间比较符号的类型
                    if(commands[i_3]!='<'&&commands[i_3+1]=='<') break;
                    if(commands[i_3]!='='&&commands[i_3+1]=='=') break;
                }
                if(i_3==int(commands.length())) return -4;//wrong cases;
                char sign=commands[i_3+1];
                int i_4;
                if(commands[i_3+2]!=' ') {i_4=i_3+1;}
                else{
                    for(i_4=i_3+1;i_4<int(commands.length());i_4++){
                        if(commands[i_4]==' '&&commands[i_4+1]!=' '){
                            break;
                        }
                    }
                }
                if(i_4==int(commands.length())){
                    return -4;
                }
                int k_1=0;
                for(k_1=i_4+1;k_1<int(commands.size());k_1++){
                    if(commands[k_1]!=' '&&commands[k_1+1]==' '){
                        break;
                    }
                }
                if(k_1==int(commands.size())) return -4;
                std::string kd(commands.begin()+i_4+1,commands.begin()+k_1+1);
                int b=0;
                expressions tmpp;
                tmpp.addexpression(kd,variables,b,false,false);
                if(tmpp.wrong==true||tmpp.equalsignal==false){
                    return -4;
                }
                if(tmpp.variablewrong==true){
                    return -6;
                }
                if(tmpp.numwrong==true){
                    return -7;
                }//wrong case
                bool flag=comparing(a,sign,b);//比较函数，返回goto某一行，或者执行下一行
                if(flag==true){
                    statement.counttimes+=1;
                    int i_5=0;
                    for(i_5=k_1+1;i_5<int(commands.size());i_5++){
                        if(commands[i_5]==' '&&commands[i_5+1]!=' ') break;
                    }
                    if(i_5==int(commands.size())) return -4;
                    int i_6=i_5;
                    for(i_6=i_5+1;i_6<int(commands.size());i_6++){
                        if(commands[i_6]!=' '&&commands[i_6+1]==' '){
                            break;
                        }
                    }
                    if(i_6==int(commands.size())) return -4;
                    std::string pd(commands.begin()+i_5+1,commands.begin()+i_6+1);
                    if(pd.compare("THEN")!=0) return -4;
                    else{
                        int i_7=0;
                        for(i_7=i_6+1;i_7<int(commands.size());i_7++){
                            if(commands[i_7]==' '&&commands[i_7+1]!=' '){
                                break;
                            }
                        }
                        if(i_7==int(commands.size())) return -1;
                        std::string num(commands.begin()+i_7+1,commands.end());
                        for(int i=0;i<int(num.size());i++){
                            if(isdigit(num[i])==0){
                                return -4;
                            }
                        }
                        int number=atoi(num.c_str());
                        return number;
                    }
                }
                else {
                    statement.relativecounttimes+=1;//counttime++;
                    return -9999;
                }
           }
           return -10;
    }
    else{
        if(commands.compare("END")==0){//end case
            return -1;//返回-1，表示程序已经执行完毕
        }
        return -10;
    }
}

bool program_line::comparing(int a, char b, int c){//比较符号
    if(b=='>'){
        if(a>c) return true;
        else return false;
    }
    if(b=='='){
        if(a==c) return true;
        else return false;
    }
    if(b=='<'){
        if(a<c) return true;
        else return false;
    }
    return false;
}

QString program_line::returncmdline(){
    QString a=QString::number(linenumber);
    QString b=" ";
    QString c=QString::fromStdString(commands);
    return a+b+c;
}

void program_line::changecmd(std::string cmd){
    commands=cmd;
}
