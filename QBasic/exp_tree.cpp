#include "exp_tree.h"
//类似expression，减去了计算的功能
void exp_trees::addexpression(std::string cmd)//添加expression
{
        bool flag=false;
        int i=0;
        if(cmd.length()==0)
            return ;
        for(i=0;i<int(cmd.length());i++){
            if(cmd[i]!=' '&&cmd[i+1]==' '){
                break;
            }
        }
        if(i==int(cmd.length())){
            std::string tmp(cmd.begin(),cmd.end());
            checktype(tmp);
            flag=true;
            if(ifdone==0){
                handleexpression();
                ifdone+=1;
            }
            return ;
        }
        else{
            std::string cmdd(cmd.begin(),cmd.begin()+i+1);
            checktype(cmdd);
            int i_1=0;
            for(i_1=0;i_1<int(cmd.length());i_1++){
                if(cmd[i_1]==' '&&cmd[i_1+1]!=' '){
                    break;
                }
            }
            std::string next(cmd.begin()+i_1+1,cmd.end());
            addexpression(next);
        }
        if(ifdone==0){
            handleexpression();//处理函数
            ifdone+=1;
        }
}

void exp_trees::checktype(std::string tmp){
    while(tmp.size()!=0){
        int i=0;int j=0;
        if(isdigit(tmp[0])==0&&whetheroperation(tmp)>0&&!(whetheroperation(tmp)==2&&ifnegative==true&&isdigit(tmp[1])!=0)){//是运算符
            int k=whetheroperation(tmp);
            if(k!=8){
                ifnegative=true;
            }
            else{
                ifnegative=false;
            }
            if(k==6) {k=2;}
            else if(k==5) {k=3;}
//            else if(k==7) {k=1; ifnegative=true;}
            else {k=1;}
            std::string tmpp(tmp.begin(),tmp.begin()+k);
            exp_tree a;
            a.code=1;
            a.type=whetheroperation(tmpp);
            switch(whetheroperation(tmpp)){
            case 1:
            case 2:  a.importance=2;
                     break;
            case 3:  a.importance=3;
                     break;
            case 4:
            case 5:  a.importance=3;
                     break;
            case 6:  a.importance=4;
                     break;
            case 7:  a.importance=0;
                     break;
            case 8:  a.importance=5;
                     break;
            case 9:  a.importance=1;
                     break;
            }
            expression_list.push_back(a);
            operation_list.push_back(a);
            std::string desti(tmp.begin()+k,tmp.end());
            tmp=desti;
        }
        else if(isdigit(tmp[0])!=0||(tmp[0]=='-'&&isdigit(tmp[1])!=0)){//是数字const
            bool flag=false;
            for(i=1;i<tmp.size();i++){
                std::string tmpp=tmp.substr(i,tmp.size());
                if(whetheroperation(tmpp)>0){
                    flag=true;
                    j=i;
                    if(whetheroperation(tmpp)==6){
                        i+=2;
                        break;
                    }
                    if(whetheroperation(tmpp)==5){
                        i+=3;
                        break;
                    }
                    else{
                        i+=1;
                        break;
                    }
                }
            }
            std::string ct;
            if(j!=0){
                std::string t(tmp.begin(),tmp.begin()+j);
                ct=t;
            }
            else{
                std::string t(tmp.begin(),tmp.end());
                ct=t;
            }
//            for(int i=1;i<ct.size();i++){
//                if(isdigit(ct[i])==0){
//                    wrong=true;
//                }
//            }
            exp_tree st;
            st.code=2;
            st.const_data=atoi(ct.c_str());
            expression_list.push_back(st);
            term_list.push_back(st);
            if(flag==false){
                ifnegative=true;
                return;
            }
            std::string desti(tmp.begin()+j,tmp.end());
            tmp=desti;
            ifnegative=false;
    }
    else{//是variables
            bool flag=false;
            for(i=1;i<tmp.size();i++){
                std::string tmpp=tmp.substr(i,tmp.size());
                if(whetheroperation(tmpp)>0){
                    flag=true;
                    j=i;
                    if(whetheroperation(tmpp)==6){
                        i+=2;
                        break;
                    }
                    if(whetheroperation(tmpp)==5){
                        i+=3;
                        break;
                    }
                    else{
                        i+=1;
                        break;
                    }
                }
            }
            std::string ct;
            if(j!=0){
                std::string t(tmp.begin(),tmp.begin()+j);
                ct=t;
            }
            else{
                std::string t(tmp.begin(),tmp.end());
                ct=t;
            }
//            if(ifexp==false){
//                for(int i=0;i<variables.size();i++){
//                    if(variables[i].name.compare(ct)==0){
//                        variables[i].existtimes+=1;
//                        break;
//                    }
//                }
////                firstexist=true;
//            }
            exp_tree st;
            st.code=3;
            st.name=ct;
            expression_list.push_back(st);
            term_list.push_back(st);
            if(flag==false){
                ifnegative=false;
                return;
            }
            std::string desti(tmp.begin()+j,tmp.end());
            tmp=desti;
            ifnegative=false;
        }
    }
    ifnegative=true;
    return;
}

void exp_trees::pushoperation(exp_tree tmp){//把operations添加到对应栈里
    if(operation_stack.empty()==true) {
        operation_stack.push(tmp);
        return;
    }
    if(tmp.importance==0) {
        operation_stack.push(tmp);
        return;
    }
    if(tmp.importance==5) {
        while(operation_stack.top().importance!=0){
            exp_tree tmpp=operation_stack.top();
            addtree(operation_stack.top());
            operation_stack.pop();
        }
        operation_stack.pop();
        return;
    }
    if(tmp.importance>operation_stack.top().importance) {
        operation_stack.push(tmp);
        return;
    }
    else{
        if(tmp.importance!=4){
            while(operation_stack.empty()!=true&&tmp.importance<=operation_stack.top().importance){
                exp_tree tmpp=operation_stack.top();
                addtree(tmpp);
                operation_stack.pop();
            }
            operation_stack.push(tmp);
            return;
        }
        else{
             while(operation_stack.empty()!=true&&tmp.importance<=operation_stack.top().importance){
                 if(operation_stack.top().importance==4) break;
                 exp_tree tmpp=operation_stack.top();
                 addtree(tmpp);
                 operation_stack.pop();
             }
             operation_stack.push(tmp);
             return;
        }
    }
}

void exp_trees::autoaddingtree(){//自动添加生成树
   addtree(operation_stack.top());
   operation_stack.pop();
}

void exp_trees::addtree(exp_tree tmp){

    exp_tree* compond=new exp_tree;
    exp_tree* tmp1=new exp_tree;
    exp_tree* tmp2=new exp_tree;
    compond->code=4;
    compond->compond_type=tmp.type;
    compond->importance=tmp.importance;
    if(term_stack.empty()==true){
        wrong=true;
//        return;
    }
    else{
        *tmp1=term_stack.top();
        term_stack.pop();
        compond->right=tmp1;
    }
    if(term_stack.empty()==true){
        wrong=true;
//        return;
    }
    else{
        *tmp2=term_stack.top();
        term_stack.pop();
        compond->left=tmp2;
    }
    term_stack.push(*compond);
    return;
}



void exp_trees::termpush(exp_tree tmp){//添加变量
    int i;
    term_stack.push(tmp);
}

int exp_trees::whetheroperation(std::string tmp){
    std::string tmp1(tmp.begin(),tmp.begin()+1);
    std::string tmp2(tmp.begin(),tmp.begin()+2);
    std::string tmp3(tmp.begin(),tmp.begin()+3);
    if(tmp1.compare("+")==0) return 1;
    if(tmp1.compare("-")==0) return 2;
    if(tmp2.compare("**")==0) return 6;
    if(tmp1.compare("*")==0) return 3;
    if(tmp1.compare("/")==0) return 4;

    if(tmp3.compare("MOD")==0) return 5;
    if(tmp1.compare("(")==0) return 7;
    if(tmp1.compare(")")==0) return 8;
    if(tmp1.compare("=")==0) {
        if(iflet==false){

            return 9;
        }

//        else{
//            equaltimes+=1;
//        }
        return 9;
    }

    return -1;
}

void  exp_trees::handleexpression(){
    if(expression_list.isEmpty()==true) {
        while(!term_stack.empty()&&!operation_stack.empty()){
            autoaddingtree();
        }
        buffer=&term_stack.top();
        return;
    }
    switch(expression_list.front().code){
    case 1: pushoperation(expression_list.front());
            expression_list.erase(expression_list.begin());
            break;
    case 2:
    case 3:
    case 4:
           termpush(expression_list.front());
           expression_list.erase(expression_list.begin());
           break;

    }
    handleexpression();
}
