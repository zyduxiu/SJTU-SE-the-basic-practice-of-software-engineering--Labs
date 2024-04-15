#include <fstream>
#include <iostream>
#include "Buffer.h"
#include <string>
//TODO: your code here
//implement the functions in ListBuffer
void editorlist::listclear(){
    node *p=head->next,*q;
    while(p!=NULL){
        q=p->next;
        delete p;
        p=q;
    }
    currentlength=0;
}
void editorlist::listdelete(int n){
    node* p=head;
    node* q;
    for(int i=0;i<n-1;i++){
        p=p->next;
    }
    q=p->next;
    p->next=q->next;
    delete q;
    currentlength--;
}
void editorlist::listinsert(int n,string st) {
    node *p=head;
    for(int i=0;i<n;i++)
    {p=p->next;}
    p->next=new node(st,p->next);
    currentlength++;
    std::cout<<"append is success!"<<currentlength<<std::endl;
}
string editorlist::listread(int n){
    node *p=head;
    for(int i=0;i<n;i++){
        p=p->next;
    }
    return p->data;
}
string& editorlist::move(int n){
    node *p=head;
    for(int i=0;i<n;i++){
        p=p->next;
    }
    return p->data;
}
void Buffer::writeToFile(const string &filename) {
    std::ofstream outfile(filename);
    int num=0;
    for(int i=1;i<=list.currentlength;i++){
        outfile<<list.listread(i);
            for(int j=0;((list.listread(i))[j]);j++){
                num++;
            }
        }
    outfile.close();
    std::cout<<num;
}
void Buffer::showLines(int from, int to) {
    for(int i=from;i<=to;i++){
        std::cout<<list.listread(i);
        std::cout<<std::endl;
    }
}
void Buffer::deleteLines(int from, int to){
    for(int i=from;i<=to;i++){
        list.listdelete(i);
    }
}
void Buffer::insertLine(string &text){
    list.listinsert(list.currentlength-1,text);
}
void Buffer::appendLine(string &text){
    if(list.currentlength==0){list.listinsert(list.currentlength-1,text);}
    else{list.listinsert(list.currentlength,text);}
}
string &Buffer::moveToLine(int idx)  {
    return list.move(idx);
}
