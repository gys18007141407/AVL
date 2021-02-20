#include "AVL.h"
#include <iostream>

AVLnode::AVLnode():m_val(0), m_BF(0), left(nullptr), right(nullptr){
}

AVLnode::AVLnode(int x):m_val(x), m_BF(0), left(nullptr), right(nullptr){
}

AVLnode::~AVLnode(){
    if(left) delete left;
    if(right) delete right;
}

AVLtree::AVLtree():root(nullptr){

}

AVLtree::AVLtree(int x):root(new AVLnode(x)){

}

AVLtree::~AVLtree(){
    if(root) delete root;
}

void AVLtree::LL(pAVLnode& cur){

    pAVLnode newroot = cur->left;
    cur->left = nullptr;
    if(newroot->right) cur->left = newroot->right;
    newroot->right = cur;
    cur = newroot;

    if(cur->left) cur->m_BF = 0;
    else cur->m_BF = -1;
    cur->right->m_BF = 0;

}

void AVLtree::RR(pAVLnode& cur){

    pAVLnode newroot = cur->right;
    cur->right = nullptr;
    if(newroot->left) cur->right = newroot->left;
    newroot->left = cur;
    cur = newroot;

    if(cur->right) cur->m_BF = 0;
    else cur->m_BF = 1;
    cur->left->m_BF = 0;
}

void AVLtree::LR(pAVLnode& cur){

    RR(cur->left);
    LL(cur);
}

void AVLtree::RL(pAVLnode& cur){
    LL(cur->right);
    RR(cur);
}

int AVLtree::insert(pAVLnode& cur,int val){

    if(nullptr == cur){
        cur = new AVLnode(val);
        return 1;
    }

    if(cur->m_val == val) return 0;

    int rval;

    if(cur->m_val > val) {

        rval = insert(cur->left, val);

        cur->m_BF += rval;

        if(cur->m_BF > 1){

            if(cur->left->m_BF == 1) {
                this->LL(cur);
            }else{
                this->LR(cur);
            }

            return 0;

        }


    }else{

        rval = insert(cur->right, val);

        cur->m_BF -= rval;

        if(cur->m_BF < -1){

            if(cur->right->m_BF == -1){
                this->RR(cur);
            }else{
                this->RL(cur);
            }

            return 0;
            
        }

    }

    return rval;
}

int AVLtree::delet(pAVLnode& cur, int val){

    if(cur == nullptr) {
        std::perror("the value not in this tree");
        return 0;
    }

    if(cur->m_val == val){

        if(!cur->left && !cur->right){
            delete cur;
            cur = nullptr;
            return 1;
        }

        if(cur->m_BF > 0){ // replace with left tree value

            pAVLnode& replace = getRightMost(cur->left); // replace->m_BF == 1 or 0

            cur->m_val = replace->m_val;

            pAVLnode temp = replace->left;

            delete replace;

            replace = temp;

            if(replace) return 0;

            return 1;

        }else{ // replace with right tree value
            pAVLnode& replace = getLeftMost(cur->right);

            cur->m_val = replace->m_val;

            pAVLnode temp = replace->right;

            delete replace;

            replace = temp;

            if(replace) return 0;

            return 1;
        }

    }else if(cur->m_val > val){
        int rval = delet(cur->left, val);

        int pre = cur->m_BF;

        if(rval == 1) cur->m_BF -= 1;

        if(cur->m_BF < -1){

            if(cur->right->m_BF == -1) RR(cur);
            else if(cur->right->m_BF == 1) RL(cur);
            else{


            }
            return 0;
        }

        return pre<0?-pre:pre;

    }else{
        int rval = delet(cur->right, val);

        int pre = cur->m_BF;

        if(rval == 1) cur->m_val += 1;

        if(cur->m_BF > 1){

            if(cur->left->m_BF == 1) LL(cur);
            else if(cur->left->m_BF == -1) LR(cur);
            else{

           
            }
            return 0;

        }

        return pre<0?-pre:pre;
    }

    return 0;

}

void AVLtree::preorder(pAVLnode& root){

    if(!root) {
        std::cout << "# ";
        return;
    }
    std::cout << root->m_val << " ";
    preorder(root->left);
    preorder(root->right);
    
}

void AVLtree::inorder(pAVLnode& root){

    if(!root) {
        std::cout << "# ";
        return;
    }
    inorder(root->left);
    std::cout << root->m_val << " ";
    inorder(root->right);
    
}

void AVLtree::pBF(pAVLnode& root){
    if(!root) {
        std::cout << "# ";
        return;
    }
    std::cout << root->m_BF << " ";
    pBF(root->left);
    pBF(root->right);
}

void AVLtree::show(){

    std::cout << "preorder:\t";
    this->preorder(this->root);
    putchar('\n');
    std::cout << "print_Bf:\t";
    this->pBF(this->root);
    putchar('\n');
    std::cout << "inorder:\t";
    this->inorder(this->root);
    putchar('\n');

}

AVLtree::pAVLnode& AVLtree::getLeftMost(pAVLnode& cur){

    if(cur->left) return getLeftMost(cur->left);

    return cur;

}

AVLtree::pAVLnode& AVLtree::getRightMost(pAVLnode& cur){

    if(cur->right) return getRightMost(cur->right);

    return cur;

}



