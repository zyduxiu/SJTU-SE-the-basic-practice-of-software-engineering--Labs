#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <queue>
#include <algorithm>

#include "Tree.h"

using namespace std;

/****************************************************************
 *                    Write your code below
 ****************************************************************/
TreeNode::~TreeNode(){}
ostream &operator<<(ostream &out, const TreeNode &b){
    out<<'('<<b.data[0]<<')'<<b.data[1];
    return out;
}
int TreeNode::getX(){
    return data[0];
}
int TreeNode::getY(){
    return data[1];
}
bool compareX(point a,point b)
{
    return a.x<b.x;
}
bool compareY(point a,point b)
{
    return a.y<b.y;
}

long long int distance(int a,int b,int x,int y){
    return ((a-x)*(a-x)+(b-y)*(b-y));
}

BinaryDimonTree::BinaryDimonTree()
{
    root=new TreeNode();
}

void BinaryDimonTree::BinaryDimonTreebuilding(TreeNode* node,point a[],int size,int k)
{
    if(size==0)
    {
        node->left=NULL;
        node->right=NULL;
        return;
    }
    if(!k)
        sort(a,a+size,compareX);
    else
        sort(a,a+size,compareY);
    node->data[0]=a[size/2].x;
    node->data[1]=a[size/2].y;
    node->height=k;
    node->left=new TreeNode;
    node->right=new TreeNode;
    if(size/2!=0)
    {
        node->left=new TreeNode;
        BinaryDimonTreebuilding(node->left,a,size/2,(node->height+1)%2);
    }
    else node->left=NULL;

    if(size-size/2-1!=0)
    {
        node->right=new TreeNode;
        BinaryDimonTreebuilding(node->right,a+size/2+1,size-size/2-1,(node->height+1)%2);
    }
    else node->right=NULL;

}

istream &operator>>(istream &in, BinaryDimonTree &tree)
{
    int pointNum,i;
    in>>pointNum;
    point point[pointNum];
    for(i=0;i<pointNum;i++){
        in>>point[i].x;
        in>>point[i].y;
    }
    tree.BinaryDimonTreebuilding(tree.root,point,pointNum,0);
    return in;
}
/*void BinaryDimonTree::BinaryDimonTreebuilding(TreeNode* node,point point[],int left,int right,int floor) {
    if(right<left){return;}
    dmp=floor;
    if(node==root){
        int mid=(left+right)/2;
        root->data[0]=point[mid].x;
        root->data[1]=point[mid].y;
        root->left=new TreeNode;
        BinaryDimonTreebuilding(node->left,point,left,mid-1,1);;
        root->right=new TreeNode;
        BinaryDimonTreebuilding(node->right,point,mid+1,right,1);
    }
    if(floor==0){
        sort(point+left,point+1+right,compareX);
    }
    if(floor==1){
        sort(point+left,point+1+right,compareY);
    }
    int mid=(left+right)/2;
    TreeNode *tmp=new TreeNode(point[mid],dmp);
    tmp->data[0]=point[mid].x;
    tmp->data[1]=point[mid].y;
    tmp->left=new TreeNode;
    BinaryDimonTreebuilding(node->left,point,left,mid-1,(floor+1)%2);;
    tmp->right=new TreeNode;
    BinaryDimonTreebuilding(node->right,point,mid+1,right,(floor+1)%2);

};*/
const long long int maxinum=10000000000000000;
TreeNode *BinaryDimonTree::find_nearest_node(int x, int y)
{

    long long int minidistance=maxinum;
    TreeNode* guess=NULL;
    recur_search(root,x,y,minidistance,&guess);
    return guess;
}

void BinaryDimonTree::recur_search( TreeNode *cur,int x, int y, long long int &min_distance, TreeNode **guess) {
    if(cur==NULL){return;}
    if(distance(cur->getX(),cur->getY(),x,y)<min_distance) {
        min_distance=distance(cur->getX(),cur->getY(),x,y);
        *guess=cur;
    }
    if(distance(cur->getX(),cur->getY(),x,y)==min_distance) {
        if(cur->data[0]<(*guess)->data[0]) {
            *guess = cur;
        }
        else if ((cur->data[0] == (*guess)->data[0]) && (cur->data[1] < (*guess)->data[1])) {
            *guess = cur;
        }
    }
    if(cur->data[cur->height]<((cur->height==0)?x:y)){
        recur_search(cur->right, x, y, min_distance, guess);
        if ((((cur->height == 0) ? x : y) - cur->data[cur->height]) *
            (((cur->height == 0) ? x : y) - cur->data[cur->height]) < min_distance) {
            recur_search(cur->left, x, y, min_distance, guess);
        }
    }
    else{
        recur_search(cur->left, x, y, min_distance, guess);
        if ((((cur->height == 0) ? x : y) - cur->data[cur->height]) *
            (((cur->height == 0) ? x : y) - cur->data[cur->height]) < min_distance) {
            recur_search(cur->right, x, y, min_distance, guess);
        }
    }
}


BinaryDimonTree::~BinaryDimonTree()
{}
