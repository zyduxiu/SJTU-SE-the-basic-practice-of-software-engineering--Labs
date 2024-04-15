#include "board.h"
#include "canvas.h"
Board::Board(int num_disk) {
    for(int i=0;i<num_disk;i++){
        a.push(num_disk-i);
    }
    num_=num_disk;
}

Board::~Board() {
    while(!a.empty()){
        a.pop();
    }
    while(!b.empty()){
        b.pop();
    }
    while(!c.empty()){
        c.pop();
    }
    while(!moving.empty()){
        moving.pop();
    }
}

void Board::draw() {
    Canvas canvas;
    canvas.reset();
    int num1,num2,num3;
    int tmp;
    for(int i=0;i<41;i++){
        canvas.buffer[10][i]='-';
    }
    for(int j=0;j<11;j++){
        canvas.buffer[j][5]='|';
    }
    for(int j=0;j<11;j++){
        canvas.buffer[j][20]='|';
    }
    for(int j=0;j<11;j++){
        canvas.buffer[j][35]='|';
    }
    Stack<int> st;
    num1=a.size();
    num2=b.size();
    num3=c.size();
    for(int j=0;j<num1;j++){
        int sw=a.top();
        for(int k=-1;k<2*sw;k++){
            canvas.buffer[11-2*num1+2*j][5-a.top()+1+k]='*';
        }
        tmp=a.top();
        a.pop();
        st.push(tmp);
    }
    for(int i=0;i<num1;i++){
        a.push(st.top());
        st.pop();
    }
    for(int j=0;j<num2;j++){
        for(int k=-b.top();k<b.top()+1;k++){
            canvas.buffer[11-2*num2+2*j][20-k]='*';
        }
        tmp=b.top();
        b.pop();
        st.push(tmp);
    }
    for(int i=0;i<num2;i++){
        b.push(st.top());
        st.pop();
    }
    for(int j=0;j<num3;j++){
        for(int k=-c.top();k<c.top()+1;k++){
            canvas.buffer[11-2*num3+2*j][35-k]='*';
        }
        tmp=c.top();
        c.pop();
        st.push(tmp);
    }
    for(int i=0;i<num3;i++){
        c.push(st.top());
        st.pop();
    }
    canvas.draw();
    // TODO
}

void Board::move(int from, int to, bool log) {
    if(log){
        if(from!=1&&from!=2&&from!=3||to!=1&&to!=2&&to!=3){throw "bad movement!";}
        else {
            if (from == 1) {
                if (a.empty()) { throw "bad movement!"; }
                if (to == 2) {
                    if(!b.empty()&&a.top()>b.top()){throw "bad movement!"; }//c++中的逻辑短路
                    else {
                        b.push(a.top());
                        a.pop();
                        moving.push(from);
                        moving.push(to);
                    }
                }
                if (to == 3) {
                    if(!c.empty()&&a.top()>c.top()){throw "bad movement";}
                    c.push(a.top());
                    a.pop();
                    moving.push(from);
                    moving.push(to);
                }
                if (to == 1 && to != 2 || to != 3) { throw "bad movement!"; }
            }
            if (from == 2) {
                if (b.empty()) { throw "bad movement!"; }
                if (to == 3) {
                    if(!c.empty()&&b.top()>c.top()){throw "bad movement";}
                    c.push(b.top());
                    b.pop();
                    moving.push(from);
                    moving.push(to);
                }
                if (to == 1) {
                    if(!a.empty()&&b.top()>a.top()){throw "bad movement";}
                    a.push(b.top());
                    b.pop();
                    moving.push(from);
                    moving.push(to);
                }
                if (to == 2 && to != 1 || to != 3) { throw "bad movement!"; }
            }
            if (from == 3) {
                if (c.empty()) { throw "bad movement!"; }
                if (to == 2) {
                    if(!b.empty()&&c.top()>b.top()){throw "bad movement";}
                    b.push(c.top());
                    c.pop();
                    moving.push(from);
                    moving.push(to);
                }
                if (to == 1) {
                    if(!a.empty()&&c.top()>a.top()){throw "bad movement";}
                    a.push(c.top());
                    c.pop();
                    moving.push(from);
                    moving.push(to);
                }
                if (to == 3 && to != 1 || to != 2) { throw "bad movement!"; }
            }
            draw();
        }
    }
    else{
        if(from==1){
            if(a.empty()){throw "bad movement!";}
            if(to==2){
                b.push(a.top());
                a.pop();
            }
            if(to==3){
                c.push(a.top());
                a.pop();
            }
        }
        if(from==2){
            if(b.empty()){throw "bad movement!";}
            if(to==3){
                c.push(b.top());
                b.pop();
            }
            if(to==1){
                a.push(b.top());
                b.pop();
            }
        }
        if(from==3){
            if(c.empty()){throw "bad movement!";}
            if(to==2){
                b.push(c.top());
                c.pop();
            }
            if(to==1){
                a.push(c.top());
                c.pop();
            }
        }
        cout<<"Auto moving:"<<from<<"->"<<to<<endl;
        draw();
    }
}

bool Board::win() {
    bool flag=true;
    if(b.size()!=num()){return false;}
    else {
        for (int i = 0; i < b.size(); i++) {
            if (b.top() != i + 1) {
                flag = false;
            }
            b.pop();
        }
    }
    return flag;
}

void Board::autoplay() {
    while(!moving.empty()){
        int x=moving.top();
        moving.pop();
        move(x,moving.top(),false);
        moving.pop();
    }
    autohanoi(num(),1,3,2);
    return;
}
void Board::autohanoi(int n,int x,int y,int z){
    if(n==0){
        return;
    }
    else{
        autohanoi(n-1,x,z,y);
        move(x,z,false);
        autohanoi(n-1,y,x,z);
    }
}
