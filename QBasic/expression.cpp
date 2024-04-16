#include "expression.h"
#include "string.h"
expression::expression()
{

}
void expressions::checkequal(){//确保let赋值时等号只有一个的函数
    if((iflet==true&&operation_list[0].type!=9)){
        equalsignal=false;
    }
    for(int i=1;i<operation_list.size();i++){
        if(operation_list[i].type==9){
            equalsignal=false;
        }
    }
}

void expressions::addexpression(std::string cmd,QVector<expression>& variables,int& a,bool ifadjust,bool ifexp){//添加expression表达式的函数
    ifadapt=ifadjust;
    bool flag=false;
    int i=0;
    if(cmd.length()==0)//空指令
        return ;
    for(i=0;i<int(cmd.length());i++){
        if(cmd[i]!=' '&&cmd[i+1]==' '){//截取字符串（递归实现）
            break;
        }
    }
    if(i==int(cmd.length())){//截断到元字符串时，递归结束
        std::string tmp(cmd.begin(),cmd.end());
        checktype(tmp,variables,ifexp);//检测该字符串类型的函数
        flag=true;
        if(ifdone==0){
            handleexpression(variables,ifadjust);//处理字符串
            if(wrong==true) return;
            checkequal();
            if(equalsignal==false){
                return;
            }
            if(counting_stack.top().code==2){
                a=counting_stack.top().const_data;
            }
            else{
                a=counting_stack.top().data;
            }
            if(ifadjust==true&&ifexp==false){
                for(int i=0;i<variables.size();i++){
                    if((buffer->left->name).compare((variables[i].name))==0){//变量未出现过
                        if(counting_stack.top().existed==true){
                            variables[i].existtimes-=1;
                        }
                        else{
                            variables[i].existed=true;
                        }
                        break;
                    }
                }
            }
            ifdone+=1;//递归结束，ifdone不为0调用函数直接返回
        }
        return ;
    }
    else{
        std::string cmdd(cmd.begin(),cmd.begin()+i+1);
        checktype(cmdd,variables,ifexp);
        int i_1=0;
        for(i_1=0;i_1<int(cmd.length());i_1++){
            if(cmd[i_1]==' '&&cmd[i_1+1]!=' '){
                break;
            }//截取字符串
        }
        std::string next(cmd.begin()+i_1+1,cmd.end());
        addexpression(next,variables,a,ifadjust,ifexp);
    }
    if(ifdone==0){//递归结束标识
        handleexpression(variables,ifadjust);
        if(wrong==true) return;
        if(counting_stack.top().code==2){
            a=counting_stack.top().const_data;
        }
        else{
            a=counting_stack.top().data;
        }
        if(ifadjust==true&&ifexp==false){
            for(int i=0;i<variables.size();i++){
                if((buffer->left->name).compare((variables[i].name))==0){
                    if(term_list[0].existed==true){
                        variables[i].existtimes-=1;
                    }
                }
            }
        }
        ifdone+=1;
    }
    else{
        return;
    }
}

void expressions::checktype(std::string tmp,QVector<expression>& variables,bool ifexp){//检测字符串表示的类型
    while(tmp.size()!=0){
        int i=0;int j=0;
        if(isdigit(tmp[0])==0&&whetheroperation(tmp)>0&&!(whetheroperation(tmp)==2&&ifnegative==true&&isdigit(tmp[1])!=0)){//是运算符号
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
            expression a;
            a.code=1;
            a.type=whetheroperation(tmpp);
            switch(whetheroperation(tmpp)){//表明哪一个运算符
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
        else if(isdigit(tmp[0])!=0||(tmp[0]=='-'&&isdigit(tmp[1])!=0&&ifnegative==true)){//是数字情况

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
            for(int i=1;i<ct.size();i++){
                if(isdigit(ct[i])==0){
                    wrong=true;
                }
            }
            expression st;
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
    else{bool flag=false;
            for(i=1;i<tmp.size();i++){//是变量variable
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
            if(ifexp==false){
                for(int i=0;i<variables.size();i++){
                    if(variables[i].name.compare(ct)==0){
                        variables[i].existtimes+=1;
                        break;
                    }
                }
//                firstexist=true;
            }
            expression st;
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

void expressions::pushoperation(expression tmp){//将数字、变量、符号添加到栈里
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
            expression tmpp=operation_stack.top();
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
                expression tmpp=operation_stack.top();
                addtree(tmpp);
                operation_stack.pop();
            }
            operation_stack.push(tmp);
            return;
        }
        else{
             while(operation_stack.empty()!=true&&tmp.importance<=operation_stack.top().importance){
                 if(operation_stack.top().importance==4) break;
                 expression tmpp=operation_stack.top();
                 addtree(tmpp);
                 operation_stack.pop();
             }
             operation_stack.push(tmp);
             return;
        }
    }
}

void expressions::autoaddingtree(){//检测到list空，自动添加栈
   addtree(operation_stack.top());
   operation_stack.pop();
}

void expressions::addtree(expression tmp){
    expression* compond=new expression;
    expression* tmp1=new expression;
    expression* tmp2=new expression;
    if(term_stack.empty()==true){
        wrong=true;
        return;
    }
    *tmp1=term_stack.top();
    term_stack.pop();
    if(term_stack.empty()==true){
        wrong=true;
        return;
    }
    *tmp2=term_stack.top();
    term_stack.pop();
    compond->code=4;
    compond->compond_type=tmp.type;
    compond->importance=tmp.importance;
    compond->right=tmp1;
    compond->left=tmp2;
    term_stack.push(*compond);
    return;
}



void expressions::termpush(expression tmp,QVector<expression>& variables){//添加变量（variables）
    int i;
    for(i=0;i<variables.size();i++){
        if(tmp.name.compare(variables[i].name)==0){
            tmp.data=variables[i].data;
            tmp.existed=true;
            break;
        }
    }
    if(i==variables.size()&&!iftop&&tmp.code==3&&ifadapt==true){
        variablewrong=true;
    }
    if(i==variables.size()&&tmp.code==3&&ifadapt==false){
        variablewrong=true;
    }
    if(iftop==true){
        term_stack.push(tmp);
        iftop=false;
    }
    else term_stack.push(tmp);
}

int expressions::whetheroperation(std::string tmp){//判断运算符号类型
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
            equalsignal=false;
            return 9;
        }
//        else{
//            equaltimes+=1;
//        }
        return 9;
    }
    if(tmp1.compare("+")!=0&&tmp1.compare("-")!=0&&tmp1.compare("*")!=0
            &&tmp1.compare("/")!=0&&tmp1.compare("(")!=0&&tmp1.compare(")")!=0
              &&tmp1.compare("=")!=0&&tmp1.compare(" ")&&isdigit(tmp1[0])==0&&isalpha(tmp1[0])==false){//异常情况（比较复杂，可能需要维护）
        wrong=true;
    }
    //wrong=true
    return -1;
}

void expressions:: handlecounting(int type){//运算函数
    int a,b;
//    if(term_list[0].code==3){
//        if(term_list[0].existed==false){
//            firstexist=true;
//            expression_list[0].existed=true;
//        }
//    }
    switch(type){
    case 1:
            if(counting_stack.top().code==2){
                a=counting_stack.top().const_data;
                counting_stack.pop();
            }
            else{
                if(counting_stack.top().existed==1){
                    a=counting_stack.top().data;
                    counting_stack.pop();
                }
            }
            if(counting_stack.top().code==2){
                counting_stack.top().const_data+=a;
            }
            else{
                if(counting_stack.top().existed==1){
                    counting_stack.top().data+=a;
                }
            }
            break;
    case 9:
            if(counting_stack.top().code==2){
                a=counting_stack.top().const_data;
                counting_stack.pop();
            }
            else{
                if(counting_stack.top().existed==1){
                    a=counting_stack.top().data;
                    counting_stack.pop();
                }
            }
            if(counting_stack.top().code==3){
                 counting_stack.top().data=a;
            }
        break;
    case 2:
            if(counting_stack.top().code==2){
                a=counting_stack.top().const_data;
                counting_stack.pop();
            }
            else{
                if(counting_stack.top().existed==1){
                    a=counting_stack.top().data;
                    counting_stack.pop();
                }
            }
            if(counting_stack.top().code==2){
                counting_stack.top().const_data-=a;
            }
            else{
                if(counting_stack.top().existed==1){
                    counting_stack.top().data-=a;
                }
            }
        break;
    case 3:
        if(counting_stack.top().code==2){
            a=counting_stack.top().const_data;
            counting_stack.pop();
        }
        else{
            if(counting_stack.top().existed==1){
                a=counting_stack.top().data;
                counting_stack.pop();
            }
        }
        if(counting_stack.top().code==2){
            counting_stack.top().const_data*=a;
        }
        else{
            if(counting_stack.top().existed==1){
                counting_stack.top().data*=a;
            }
        }
        break;
    case 4:
        if(counting_stack.top().code==2){
            a=counting_stack.top().const_data;
            counting_stack.pop();
        }
        else{
            if(counting_stack.top().existed==1){
                a=counting_stack.top().data;
                counting_stack.pop();
            }
        }
        if(counting_stack.top().code==2){
            if(a==0){numwrong=true; return;}
            counting_stack.top().const_data/=a;
        }
        else{
            if(counting_stack.top().existed==1){
                if(a==0){numwrong=true; return;}
                counting_stack.top().data/=a;
            }
        }
        break;
    case 5:
        if(counting_stack.top().code==2){
            a=counting_stack.top().const_data;
            counting_stack.pop();
        }
        else{
            if(counting_stack.top().existed==1){
                a=counting_stack.top().data;
                counting_stack.pop();
            }
        }
        if(a==0){numwrong=true; return;}
        if(counting_stack.top().code==2){
            b=counting_stack.top().const_data/a;
            if(a*counting_stack.top().const_data<0){
                int c=counting_stack.top().const_data-(b-1)*a;
                if(c==a){counting_stack.top().const_data=0;}
                else counting_stack.top().const_data-=(b-1)*a;}
            else {
                int c=counting_stack.top().const_data-(b)*a;
                if(c==a){counting_stack.top().const_data=0;}
                else counting_stack.top().const_data-=b*a;
            }
        }
        else{
            if(counting_stack.top().existed==1){
                b=counting_stack.top().data/a;
                if(a*counting_stack.top().data<0){
                    int c=counting_stack.top().const_data-(b-1)*a;
                    if(c==a){counting_stack.top().const_data=0;}
                    else counting_stack.top().data-=(b-1)*a;}
                else {
                    int c=counting_stack.top().const_data-(b)*a;
                    if(c==a){counting_stack.top().const_data=0;}
                    else counting_stack.top().data-=(b)*a;
                }
            }
        }
        break;
    case 6:
        if(counting_stack.top().code==2){
            a=counting_stack.top().const_data;
            counting_stack.pop();
        }
        else{
            if(counting_stack.top().existed==1){
                a=counting_stack.top().data;
                counting_stack.pop();
            }
        }
        if(counting_stack.top().code==2){
            if(a==0){
                b=counting_stack.top().const_data;
                if(a==0&&b==0){numwrong=true; return;}
                counting_stack.top().const_data=1;
            }
            else{
                b=counting_stack.top().const_data;
                for(int i=0;i<a-1;i++){
                    counting_stack.top().const_data*=b;
                }
            }
        }
        else{
            if(a==0){
                b=counting_stack.top().data;
                if(a==0&&b==0){numwrong=true; return;}
                counting_stack.top().data=1;
            }
            else{
                b=counting_stack.top().data;
                for(int i=0;i<a-1;i++){
                     counting_stack.top().data*=b;
                }
            }
        }
        break;
    }
    return;
}

void expressions::countingnum(expression *node){
    if(wrong==false){
        if(node==NULL) return;
        if(node->left!=NULL){
            countingnum(node->left);
        }
        if(node->right!=NULL){
            countingnum(node->right);
        }
        switch(node->code){
        case 2:
        case 3:counting_stack.push(*node);
            break;
        case 4:handlecounting(node->compond_type);
        }
    }
    else return;

}

void  expressions::handleexpression(QVector<expression>& variables,bool ifadjust){//处理expression的框架函数
    if(wrong==true) return;
    if(expression_list.isEmpty()==true) {
        while(!term_stack.empty()&&!operation_stack.empty()){
            autoaddingtree();
        }
        buffer=&term_stack.top();
        countingnum(buffer);
        if(ifadjust==false) return;
        if(wrong==true) return;
        if(counting_stack.top().code==3){
            if(counting_stack.top().existed==false){
                variables.push_back(counting_stack.top());
            }
            else{
                int i=0;
                for(i=0;i<variables.size();i++){
                    if(variables[i].name.compare(counting_stack.top().name)==0){
                        variables[i].data=counting_stack.top().data;
                        break;
                    }
                }
            }
        }
            return;
    }
    switch(expression_list.front().code){
    case 1: pushoperation(expression_list.front());
            expression_list.erase(expression_list.begin());
            break;
    case 2:
    case 3:
    case 4:
           termpush(expression_list.front(),variables);
           expression_list.erase(expression_list.begin());
           break;

    }
    handleexpression(variables,ifadjust);
}
