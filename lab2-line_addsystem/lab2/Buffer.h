#pragma once
#include <string>
using std::string;
class editorlist{
private:struct node{
        string data;
        node *next;
        node():next(NULL){};
        node(string a):data(a),next(NULL){};
        node(string a,node* n):data(a),next(n){};};
    node* head;
public:
    int currentlength=0;
    void listclear();
    void listinsert(int n,string a);
    string listread(int n) ;
    void listdelete(int n);
    editorlist(){};
    string& move(int n);
    ~editorlist(){listclear();delete head;}
};
class Buffer {
private:
    editorlist list;
    // TODO: add a List here for storing the input lines
public:
    Buffer(){};
    void writeToFile(const string &filename) ;
    string &moveToLine(int idx) ;
    void showLines(int from, int to);
    void deleteLines(int from, int to);
    void insertLine(string &text);
    void appendLine(string &text);
};
