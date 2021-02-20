#include "AVL.h"

int main(){

    AVLtree avl;

    for(int i = 1; i<10; ++i) avl.insert(avl.root, i);
    
    avl.show();

    avl.delet(avl.root, 5);

    avl.show();

    avl.delet(avl.root, 1);

    avl.show();



    return 0;
}