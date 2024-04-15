#pragma once

#include <cassert>

template <typename T> class Queue {
    // TODO
private:
    struct node{
        T data;
        node *next;
        node(const T& x,node *y=NULL):data(x),next(y){};
        node():next(NULL){};
    };
    node *front,*rear;
    int size_=0;
public:
    Queue() {
        front=rear=NULL;
        // TODO
    }

    ~Queue() {
        node *tmp;
        while(front!=NULL){
            tmp=front;
            front=front->next;
            delete tmp;
        }
    }
    int size() const {
        return size;// TODO
    }
    bool empty() {
        return size() == 0;
    }
    void push(T t) {
        if(rear==NULL){
            front=rear=new node(t);
        }
        else rear=rear->next=new node(t);
        // TODO
    }

    void pop() {
        node *tmp=front;// TODO
        T value=front->data;
        front=front->next;
        if(front==NULL) rear=NULL;
        delete tmp;
    }
    T& head() const {
        return front->data;
        // TODO
    }

    T& back() const {
        return rear->data;
        // TODO
    }
};
