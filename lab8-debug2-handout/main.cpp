#include "tree.h"

using namespace std;
#include <cassert>
#include <string.h>


int main() {
    tree_t tree(4);
    int num=100;
    int a[1000];
    int b[1000];
    for(int i=1;i<2*108+1;i+=2){
        tree.set(i,i*2);
    }
    for(int i=1;i<109;i+=2){
        tree.remove(i);
    }
    for(int i=109;i<2*108+1;i+=2){
        auto v=tree.get(i);
        assert(v==i*2);
    }
 tree_t tree1(13);
 for(int i=1;i<1000;i++){
     tree1.set(i,i);
 }
 for(int i=407;i<1000;i++){
     tree1.remove(i);
 }
    tree_t tree2(4);
    for(int i=1;i<1000;i++){
        tree2.set(i,i);
    }
    for(int i=407;i<1000;i++){
        tree2.remove(i);
    }
//tree.set(1,1);
//tree.set(1,2);


//   tree.set(1, 42);
//  auto v = tree.get(1);
//  assert(v == 42);
//  tree.remove(1);
//  tree.set(2,7);
//  tree.set(3,9);
//  tree.set(6,8);
//  tree.set(7,13);
//  tree.set(9,212);
//  tree.remove(9);
//  tree.set(7,13);
//  tree.set(9,212);
//  tree.set(11,13);
//  tree.set(13,15);
//  tree.set(14,16);
//  tree.remove(11);
//  tree.remove(14);
//  tree.remove(2);
//  tree.remove(3);
//  tree.remove(6);
//  auto vv=tree.get(7);
//  assert(vv==13);
//  tree.~tree_t();
//  tree_t tree2(3);
//  tree2.set(1,12);
//  tree2.set(2,13);
//  node_t* node1=tree2.find_leaf(1);
//  node_t* node2=tree2.find_leaf(2);
 // std::tuple node3(3,node1,node2);
//  tree2.set(4,6);
  //tree2.insert(node3);
 // auto v2=tree2.get(4);
 // assert(v2==6);

//  tree_t tree4(4);
//  for(int i=20;i<100;i++){
//        tree4.set(i,i);
//   }
//
//for(int i=25;i<100;i++){
//   tree4.remove(i);
//}
//auto v3=tree4.get(21);
//assert(v3==21);
//  tree_t tree3(3);
//    tree3.set(1,12);
//    tree3.set(2,13);
//    tree3.remove(2);
//    tree3.remove(1);
//    tree3.set(2,14);
//    auto v3=tree3.get(2);
    
    
 

  return 0;
}
