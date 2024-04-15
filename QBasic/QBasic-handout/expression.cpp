#include "expression.h"
#include "string.h"
expression::expression()
{

}

void expressions::addexpression(std::string cmd,QVector<expression>& variables,int& a,bool ifadjust,bool ifexp){
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
        checktype(tmp,variables,ifexp);
        flag=true;
        if(ifdone==0){
            handleexpression(variables,ifadjust);
            if(counting_stack.top().code==2){
                a=counting_stack.top().const_data;
            }
            else{
                a=counting_stack.top().data;
            }
            if(ifadjust==true&&ifexp==false){
                for(int i=0;i<variables.size();i++){
                    if((buffer->left->name).compare((variables[i].name))==0){
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
            ifdone+=1;
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
            }
        }
        std::string next(cmd.begin()+i_1+1,cmd.end());
        addexpression(next,variables,a,ifadjust,ifexp);
    }
    if(ifdone==0){
        handleexpression(variables,ifadjust);
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

void expressions::checktype(std::string tmp,QVector<expression>& variables,bool ifexp){
    while(tmp.size()!=0){
        int i=0;int j=0;
        if(isdigit(tmp[0])==0&&whetheroperation(tmp)>0&&!(whetheroperation(tmp)==2&&ifnegative==true&&isdigit(tmp[1])!=0)){
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
        else if(isdigit(tmp[0])!=0||(tmp[0]=='-'&&isdigit(tmp[1])!=0&&ifnegative==true)){
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

void expressions::pushoperation(expression tmp){
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

void expressions::autoaddingtree(){
   addtree(operation_stack.top());
   operation_stack.pop();
}

void expressions::addtree(expression tmp){
    expression* compond=new expression;
    expression* tmp1=new expression;
    expression* tmp2=new expression;
    *tmp1=term_stack.top();
    term_stack.pop();
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



void expressions::termpush(expression tmp,QVector<expression>& variables){
    int i;
    for(i=0;i<variables.size();i++){
        if(tmp.name.compare(variables[i].name)==0){
            tmp.data=variables[i].data;
            tmp.existed=true;
            break;
        }
    }
//    if(i==variables.size()){
//        firstexist=true;
//    }
    term_stack.push(tmp);
}

int expressions::whetheroperation(std::string tmp){
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
    if(tmp1.compare("=")==0) return 9;
    return -1;
}

void expressions:: handlecounting(int type){
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
            counting_stack.top().const_data/=a;
        }
        else{
            if(counting_stack.top().existed==1){
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
        if(counting_stack.top().code==2){
            b=counting_stack.top().const_data/a;
            counting_stack.top().const_data-=b*a;
        }
        else{
            if(counting_stack.top().existed==1){
                b=counting_stack.top().data/a;
                counting_stack.top().data-=b*a;
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
    if(node==NULL) return;
    countingnum(node->left);
    countingnum(node->right);
    switch(node->code){
    case 2:
    case 3:counting_stack.push(*node);
          break;
    case 4:handlecounting(node->compond_type);
    }

}

void  expressions::handleexpression(QVector<expression>& variables,bool ifadjust){
    if(expression_list.isEmpty()==true) {
        while(!term_stack.empty()&&!operation_stack.empty()){
            autoaddingtree();
        }
        buffer=&term_stack.top();
        countingnum(buffer);
        if(ifadjust==false) return;
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
