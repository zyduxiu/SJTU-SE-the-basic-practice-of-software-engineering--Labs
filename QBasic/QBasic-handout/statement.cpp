#include "statement.h"

statement::statement()
{

}

void statements::addstatement(QString cmd){
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
        if(statementlist.size()!=0){
            for(j=0;j<statementlist.size();j++){
                if(num<statementlist[j].linenumber){
                     break;
                }
                if(num==statementlist[j].linenumber){
                    statementlist.erase(statementlist.begin()+j);
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
    if(statementlist.size()!=0){
        for(j=0;j<statementlist.size();j++){
            if(num<statementlist[j].linenumber){
                break;
            }
            if(num==statementlist[j].linenumber){
                if(tmp2.size()!=0){
                    statementlist[j].changetmp(tmp2);
                }
                else statementlist.erase(statementlist.begin()+j);
                return;
            }
        }
        if(j!=statementlist.size()){
            statement tmpp(num,tmp2);
            statementlist.insert(statementlist.begin()+j,tmpp);
            return;
        }
        else{
            if(tmp2.size()!=0){
                statement tmpp(num,tmp2);
                statementlist.push_back(tmpp);
                return;
            }
            return;
        }
    }
    else{
        if(tmp2.size()!=0){
            statement tmpp(num,tmp2);
            statementlist.push_back(tmpp);
            return;
        }
        return;
    }
}

void statements::runexp(QVector<expression> variables){
    for(int i=0;i<statementlist.size();i++){
        statementlist[i].afterrun(variables);
    }
    return;
}

void statement::afterrun(QVector<expression> variable){
    int i=0;
    for(i=0;i<int(commands.length());i++){
        if(commands[i]!=' '&&commands[i+1]==' '){
             break;
        }
    }
    if(i!=int(commands.length())){
        std::string type(commands.begin(),commands.begin()+i+1);
        if(type.compare("LET")==0){
            this->statementype=1;
            int i_1=0;
            for(i_1=0;i_1<commands.length();i_1++){
                if(commands[i_1]==' '&&commands[i_1+1]!=' '){
                    break;
                }
            }
            std::string next(commands.begin()+i_1+1,commands.end());
            expressions *tmp=new expressions;
            int useless;
            tmp->addexpression(next,variable,useless,false,true);
            this->tree1=tmp->buffer;
        }
        if(type.compare("PRINT")==0){
            int i_1=0;
            this->statementype=2;
            for(i_1=0;i_1<int(commands.length());i_1++){
                if(commands[i_1]==' '&&commands[i_1+1]!=' '){
                    break;
                }
            }
            std::string next(commands.begin()+i_1+1,commands.end());
            int a;
            expressions *tmp=new expressions;
            tmp->addexpression(next,variable,a,false,true);
            this->tree1=tmp->buffer;
           }
        if(type.compare("GOTO")==0){
            this->statementype=3;
            int i_1=0;
            for(i_1=0;i_1<int(commands.length());i_1++){
                if(commands[i_1]==' '&&commands[i_1+1]!=' '){
                    break;
                }
            }
            std::string next(commands.begin()+i_1+1,commands.end());
            int linenum=atoi(next.c_str());
            this->gotonumber=linenum;
        }
        if(type.compare("IF")==0){
            this->statementype=4;
            int i_1=0;
            for(i_1=0;i_1<int(commands.length());i_1++){
                if(commands[i_1]==' '&&commands[i_1+1]!=' '){
                    break;
                }
            }
            int i_2=0;
            for(i_2=i_1;i_2<int(commands.length());i_2++){
                if(commands[i_2]!=' '&&commands[i_2+1]==' ') break;
                if(commands[i_2]!='>'&&commands[i_2+1]=='>') break;
                if(commands[i_2]!='<'&&commands[i_2+1]=='<') break;
                if(commands[i_2]!='='&&commands[i_2+1]=='=') break;
            }
            std::string cd(commands.begin()+i_1+1,commands.begin()+i_2+1);
            int a=0;
            expressions *tmp=new expressions;
            tmp->addexpression(cd,variable,a,false,true);
            this->tree1=tmp->buffer;
            int i_3=0;
            for(i_3=i_2;i_3<int(commands.length());i_3++){
                if(commands[i_3]!='>'&&commands[i_3+1]=='>') break;
                if(commands[i_3]!='<'&&commands[i_3+1]=='<') break;
                if(commands[i_3]!='='&&commands[i_3+1]=='=') break;
            }
            char sign=commands[i_3+1];
            this->sign=sign;
            int i_4;
            if(commands[i_3+2]!=' ') {i_4=i_3+1;}
            else{
                for(i_4=i_3+1;i_4<int(commands.length());i_4++){
                    if(commands[i_4]==' '&&commands[i_4+1]!=' '){
                        break;
                    }
                }
            }
            int k_1=0;
            for(k_1=i_4+1;k_1<commands.size();k_1++){
                if(commands[k_1]!=' '&&commands[k_1+1]==' '){
                    break;
                }
            }
            std::string kd(commands.begin()+i_4+1,commands.begin()+k_1+1);
            int b=0;
            expressions *tmpp=new expressions;
            tmpp->addexpression(kd,variable,b,false,true);
            this->tree2=tmpp->buffer;
            int i_5=0;
            for(i_5=k_1+1;i_5<commands.size();i_5++){
                  if(commands[i_5]==' '&&commands[i_5+1]!=' ') break;
            }
            int i_6=i_5;
            for(i_6=i_5+1;i_6<commands.size();i_6++){
                 if(commands[i_6]!=' '&&commands[i_6+1]==' '){
                     break;
                 }
             }
             std::string pd(commands.begin()+i_5+1,commands.begin()+i_6+1);
             int i_7=0;
             for(i_7=i_6+1;i_7<commands.size();i_7++){
                 if(commands[i_7]==' '&&commands[i_7+1]!=' '){
                      break;
                  }
             }
             std::string num(commands.begin()+i_7+1,commands.end());
             int number=atoi(num.c_str());
             this->gotonumber=number;
        }
        if(type.compare("INPUT")==0){
            int i_1=0;
            this->statementype=5;
            for(i_1=0;i_1<int(commands.length());i_1++){
                if(commands[i_1]==' '&&commands[i_1+1]!=' '){
                    break;
                }
            }
            std::string next(commands.begin()+i_1+1,commands.end());
            this->name=next;
        }
        if(type.compare("REM")==0){
            int i_1=0;
            this->statementype=6;
            for(i_1=0;i_1<int(commands.length());i_1++){
                if(commands[i_1]==' '&&commands[i_1+1]!=' '){
                    break;
                }
            }
            std::string next(commands.begin()+i_1+1,commands.end());
            this->name=next;
        }

    }
    else{
        std::string type(commands.begin(),commands.end());
        if(type.compare("END")==0){
            this->statementype=7;
        }
    }
}
