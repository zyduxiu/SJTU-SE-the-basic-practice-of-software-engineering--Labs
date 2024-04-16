#include "statement.h"
#include "exp_tree.h"
statement::statement()
{

}

void statements::addstatement(QString cmd){//添加语法树
    int i=0;int j=0;
    for(i=0;i<cmd.length();i++){
        if(cmd[i]!=' '&&cmd[i+1]==' '){
            break;
        }
    }
    std::string cmd2=cmd.toStdString();
    std::string tmp(cmd2.begin(),cmd2.begin()+i+1);
    int num=atoi(tmp.c_str());
    if(i==cmd.length()){//如果后续command为空
        if(statementlist.size()!=0){//statementlist不为空时
            for(j=0;j<statementlist.size();j++){
                if(num<statementlist[j].linenumber){
                     break;
                }
                if(num==statementlist[j].linenumber){
                    statementlist.erase(statementlist.begin()+j);//删除某一个statemen
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
        if(cmd[i]==' '&&cmd[i+1]!=' '){//截取字符串
            break;
        }
    }
    std::string tmp2(cmd2.begin()+i+1,cmd2.end());
    if(statementlist.size()!=0){//statementlist不为空
        for(j=0;j<statementlist.size();j++){
            if(num<statementlist[j].linenumber){
                break;
            }
            if(num==statementlist[j].linenumber){
                if(tmp2.size()!=0){
                    statementlist[j].changetmp(tmp2);//改变某一个statement
                }
                else statementlist.erase(statementlist.begin()+j);//删除某个statement
                return;
            }
        }
        if(j!=statementlist.size()){
            statement tmpp(num,tmp2);
            statementlist.insert(statementlist.begin()+j,tmpp);//插入某个statement在合适的位置
            return;
        }
        else{//在list最后
            if(tmp2.size()!=0){//list不为空
                statement tmpp(num,tmp2);
                statementlist.push_back(tmpp);//直接push进去
                return;
            }
            return;
        }
    }
    else{//statementlist为空
        if(tmp2.size()!=0){
            statement tmpp(num,tmp2);
            statementlist.push_back(tmpp);//直接push
            return;
        }
        return;
    }
}

void statements::runexp(){//执行exptree
    for(int i=0;i<statementlist.size();i++){
        statementlist[i].afterrun();
        if(statementlist[i].err==true){
            statementlist[i].statementype=-4;
        }
    }
    return;
}

void statement::afterrun(){
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
            for(i_1=0;i_1<int(commands.length());i_1++){//截取字符串
                if(commands[i_1]==' '&&commands[i_1+1]!=' '){
                    break;
                }
            }
            std::string next(commands.begin()+i_1+1,commands.end());
            exp_trees *tmp=new exp_trees;
           // int useless;
            tmp->addexpression(next);
            this->tree1=tmp->buffer;
        }
        if(type.compare("PRINT")==0){//PRINT CASE
            int i_1=0;
            this->statementype=2;
            for(i_1=0;i_1<int(commands.length());i_1++){
                if(commands[i_1]==' '&&commands[i_1+1]!=' '){
                    break;
                }
            }
            std::string next(commands.begin()+i_1+1,commands.end());
          //  int a;
            exp_trees *tmp=new exp_trees;
            tmp->addexpression(next);
            this->tree1=tmp->buffer;
           }
        if(type.compare("GOTO")==0){//GOTO CASE
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
        if(type.compare("IF")==0){//IF CASE
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
            //int a=0;
            exp_trees *tmp=new exp_trees;
            tmp->addexpression(cd);
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
            for(k_1=i_4+1;k_1<int(commands.size());k_1++){
                if(commands[k_1]!=' '&&commands[k_1+1]==' '){
                    break;
                }
            }
            std::string kd(commands.begin()+i_4+1,commands.begin()+k_1+1);
            //int b=0;
             exp_trees *tmpp=new exp_trees;
            tmpp->addexpression(kd);
            this->tree2=tmpp->buffer;
            int i_5=0;
            for(i_5=k_1+1;i_5<int(commands.size());i_5++){
                  if(commands[i_5]==' '&&commands[i_5+1]!=' ') break;
            }
            int i_6=i_5;
            for(i_6=i_5+1;i_6<int(commands.size());i_6++){
                 if(commands[i_6]!=' '&&commands[i_6+1]==' '){
                     break;
                 }
             }
             std::string pd(commands.begin()+i_5+1,commands.begin()+i_6+1);
             if(pd!="THEN"){
                err=true;
                return;
             }
             int i_7=0;
             for(i_7=i_6+1;i_7<int(commands.size());i_7++){
                 if(commands[i_7]==' '&&commands[i_7+1]!=' '){
                      break;
                  }
             }
             std::string num(commands.begin()+i_7+1,commands.end());
//             if(num.size()==0){
//                 return;
//             }
             int number=atoi(num.c_str());
             this->gotonumber=number;
        }
        if(type.compare("INPUT")==0){//INPUT CASE
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
