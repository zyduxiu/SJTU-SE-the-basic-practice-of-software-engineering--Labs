#pragma once
#include "stack.h"
#include "queue.h"
#include "canvas.h"
class Board {
private:
    Stack<int>a,b,c;
    Stack<int>moving;
    int num_=0;

public:
    int num(){return num_;}
    Board(int num_disk);
    ~Board();
    void draw();
    void move(int from, int to, bool log = false);
    bool win();
    void autoplay();
    void autohanoi(int n,int x,int y,int z);
};