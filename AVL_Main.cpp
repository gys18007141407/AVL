#include "AVL_Tree.hpp"


int main(int argc, char** argv){

    CAVLTree<int> avl;

    for(int i = 1; i<20; ++i) avl.insert(i), avl.showPreorder();
    for(int i = 5; i<10; ++i) avl.remove(i), avl.showPreorder(), avl.showBF();

    return 0;
}