#ifndef C_BINARYDIMEN_TREE_H
#define C_BINARYDIMEN_TREE_H

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

/****************************************************************
 *                    Write your code below
 ****************************************************************/

class TreeNode
{
  friend ostream &operator<<(ostream &out, const TreeNode &b);
  friend class BinaryTree;
  friend class BinaryDimonTree;
private:
  /* data */
   int data[2];
   TreeNode* left;
   TreeNode* right;
   int height;
public:
  /* methods */
  TreeNode():left(NULL),right(NULL),height(0){data[0]=0;data[1]=0;};
  int getX();  /* DO NOT CHANGE */
  int getY();  /* DO NOT CHANGE */
  ~TreeNode(); /* DO NOT CHANGE */
};
struct point
{
    int x;
    int y;
};

class BinaryDimonTree
{
friend istream &operator>>(istream &in, BinaryDimonTree &tree); /* DO NOT CHANGE */

private:
  /* data */
  TreeNode *root;
  /* methods */
  void BinaryDimonTreebuilding(TreeNode* node,point point[],int size,int k);

public:
  /* methods */
  BinaryDimonTree();          /* DO NOT CHANGE */
  TreeNode *find_nearest_node(int x, int y);  /* DO NOT CHANGE */
  void recur_search(TreeNode *cur, int x, int y, long long int &min_distance, TreeNode **guess);
  ~BinaryDimonTree();
};
#endif //C_BINARYDIMEN_TREE_H
