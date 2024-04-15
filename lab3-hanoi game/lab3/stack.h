#pragma once
#include <cassert>
#include <iostream>
template <typename T> class Stack {
private:
    struct node{
        T data;
        node *next;
        node():next(NULL){};
        node(const T& x,node *y=NULL):data(x),next(y){};
        ~node(){};
    };
    // TODO
    node *top_p;
    int size_=0;
public:
    Stack() {
        top_p=NULL;  // TODO
    }

    ~Stack() {
        node *tmp;
        while(top_p!=NULL){
            tmp=top_p;
            top_p=top_p->next;
            delete tmp;
        }// TODO
    }

    int size() {
        return size_;
        // TODO
    }

    bool empty() {
        return size() == 0;
    }

    void push(T t) {
        top_p=new node(t,top_p);
        size_++;
    }

    void pop() {
        node *st;
        st=top_p;
        top_p=top_p->next;
        delete st;
        size_--;
    }
    T& top() const{
        return top_p->data;
        // TODO
    }
};
