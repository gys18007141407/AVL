#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include "AVL_Node.hpp"

template<typename T>
class CAVLTree{

public:
    typedef CAVLNode<T>* pNode;
    typedef CAVLTree* pTree;

    explicit CAVLTree();
    explicit CAVLTree(T val);
    ~CAVLTree();

    bool insert(T val);

    bool remove(T val);

    void showPreorder();

    void showBF();

private:
    pNode proot;

    void showPreorder(pNode& cur);

    void showBF(pNode& cur);

    int insert(pNode& cur, T val);

    int remove(pNode& cur, T val);

    void LL(pNode& cur);
    void RR(pNode& cur);
    void LR(pNode& cur);
    void RL(pNode& cur);

    pNode& getPrior(pNode cur);
    pNode& getNext(pNode cur);
    pNode& getMostRight(pNode& cur);
    pNode& getMostLeft(pNode& cur);

};

template<typename T>
CAVLTree<T>::CAVLTree():proot(nullptr){

}

template<typename T>
CAVLTree<T>::CAVLTree(T val):proot(new CAVLNode<T>(val)){

}

template<typename T>
CAVLTree<T>::~CAVLTree(){
    if(this->proot) delete this->proot;
}

template<typename T>
void CAVLTree<T>::showPreorder(){
    std::cout << "preorder:\t";
    this->showPreorder(this->proot);
    std::cout << std::endl;
}


template<typename T>
void CAVLTree<T>::showPreorder(pNode& cur){
    std::cout.width(4);
    if(!cur) {
        std::cout << "#";
        return;
    }
    std::cout << cur->m_val;
    showPreorder(cur->pleft);
    showPreorder(cur->pright);
}

template<typename T>
void CAVLTree<T>::showBF(){
    std::cout << "--B--F--:\t";
    this->showBF(this->proot);
    std::cout << std::endl;
}

template<typename T>
void CAVLTree<T>::showBF(pNode& cur){
    std::cout.width(4);
    if(!cur) {
        std::cout << "#";
        return;
    }
    std::cout << cur->m_BF;
    showBF(cur->pleft);
    showBF(cur->pright);
}

template<typename T>
bool CAVLTree<T>::insert(T val){
    return -1 != this->insert(this->proot, val);
}

template<typename T>
int CAVLTree<T>::insert(pNode& cur, T val){
    if(nullptr == cur){

        cur = new CAVLNode<T>(val);

        return 1;

    }

    if(cur->m_val == val) return 0;

    int return_val = 0;

    if(cur->m_val > val){

        return_val = this->insert(cur->pleft, val);

        cur->m_BF += return_val;

        if(cur->m_BF > 1){

            if(cur->pleft->m_BF == 1) LL(cur);
            else LR(cur);    // cur->pleft->m_BF == -1

            return_val = 0;
        }

    }else{

        return_val = this->insert(cur->pright, val);

        cur->m_BF -= return_val;

        if(cur->m_BF < -1){

            if(cur->pright->m_BF == -1) RR(cur);
            else RL(cur);   // cur->pright->m_BF == 1

            return_val = 0;
        }

    }

    return return_val;
}

template<typename T>
bool CAVLTree<T>::remove(T val){
    return -1 != this->remove(this->proot, val);
}

template<typename T>
int CAVLTree<T>::remove(pNode& cur, T val){

    if(nullptr == cur){
        std::cout << "this val is not in the tree ! " << std::endl;
        return -1;
    }

    int return_value = 0;

    if(cur->m_val == val){   // return 1 if cur height has decreased else return 0

        if(!cur->pleft && !cur->pright){
            delete cur;
            cur = nullptr;
            return_value = 1;
        }else{

            if(cur->m_BF > 0){  // replace cur value with prior value (left)

                pNode& prior = this->getPrior(cur);

                T replace_value = prior->m_val;

                return_value = remove(this->proot, replace_value);

                cur->m_val = replace_value;


            }else{   // replace cur value with next value (right)

                pNode& next = this->getNext(cur);

                T replace_value = next->m_val;

                return_value = remove(this->proot, replace_value);

                cur->m_val = replace_value;

            }
        }

    }else if(cur->m_val > val){  // return_value == 1 means height has decreased

        return_value = remove(cur->pleft, val);
        // if( check(return_value) ) then do something;

        cur->m_BF -= return_value;

        if(cur->m_BF < -1){
            if(cur->pright->m_BF == -1){
                RR(cur);
            }else if(cur->pright->m_BF == 1){
                RL(cur);
            }else{
                pNode inherit = cur->pright;
                cur->pright = inherit->pleft;
                inherit->pleft = cur;
                cur = inherit;

                cur->m_BF = 1;
                cur->pleft->m_BF = -1;

                return_value = 0;    // unlike two operations above, this operation will not decrease cur height

            }

        }else{
            if(return_value == 1){
                
                return_value = cur->m_BF?0:1;
            }
            
        }

    }else{

        return_value = remove(cur->pright, val);
        // if( check(return_value) ) then do something; 

        cur->m_BF += return_value;

        if(cur->m_BF > 1){
            if(cur->pleft->m_BF == 1){
                LL(cur);
            }else if(cur->pleft->m_BF == -1){
                LR(cur);
            }else{
                pNode inherit = cur->pleft;
                cur->pleft = inherit->pright;
                inherit->pright = cur;
                cur = inherit;

                cur->m_BF = -1;
                cur->pright->m_BF = 1;

                return_value = 0;

            }
        }else{
            if(return_value == 1){

                return_value = cur->m_BF?0:1;

            }
        }
    }

    return return_value;
}

template<typename T>
void CAVLTree<T>::LL(pNode& cur){

    pNode inherit = cur->pleft;
    cur->pleft = inherit->pright;
    inherit->pright = cur;
    cur = inherit;

    inherit->m_BF = inherit->pright->m_BF = 0;

}

template<typename T>
void CAVLTree<T>::RR(pNode& cur){

    pNode inherit = cur->pright;
    cur->pright = inherit->pleft;
    inherit->pleft = cur;
    cur = inherit;

    inherit->m_BF = inherit->pleft->m_BF = 0;
    
}

template<typename T>
void CAVLTree<T>::LR(pNode& cur){
    
    RR(cur->pleft);
    LL(cur);

}

template<typename T>
void CAVLTree<T>::RL(pNode& cur){

    LL(cur->pright);
    RR(cur);
    
}

template<typename T>
typename CAVLTree<T>::pNode& CAVLTree<T>::getPrior(pNode cur){
    return getMostRight(cur->pleft);
}

template<typename T>
typename CAVLTree<T>::pNode& CAVLTree<T>::getNext(pNode cur){
    return getMostLeft(cur->pright);
}

template<typename T>
typename CAVLTree<T>::pNode& CAVLTree<T>::getMostRight(pNode& cur){
    if(cur->pright) return getMostRight(cur->pright);
    return cur;
}

template<typename T>
typename CAVLTree<T>::pNode& CAVLTree<T>::getMostLeft(pNode& cur){
    if(cur->pleft) return getMostLeft(cur->pleft);
    return cur;
}

#endif