#ifndef AVL_NODE_HPP
#define AVL_NODE_HPP

#include <iostream>


template<typename T>
class CAVLNode{

public:
    CAVLNode();
    CAVLNode(T val);
    ~CAVLNode();


    T m_val;
    int m_BF;
    CAVLNode* pleft;
    CAVLNode* pright;


};

template<typename T>
CAVLNode<T>::CAVLNode():m_val(0), m_BF(0), pleft(nullptr), pright(nullptr){

}


template<typename T>
CAVLNode<T>::CAVLNode(T val):m_val(val), m_BF(0), pleft(nullptr), pright(nullptr){

}

template<typename T>
CAVLNode<T>::~CAVLNode(){
    if(this->pleft) delete this->pleft;
    if(this->pright) delete this->pright;
}



#endif