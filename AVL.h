

class AVLnode{
public:
    explicit AVLnode();
    explicit AVLnode(int);

    ~AVLnode();

    int m_val;
    int m_BF;
    AVLnode* left;
    AVLnode* right;
};

class AVLtree{
public:
    typedef AVLnode* pAVLnode;
    explicit AVLtree();
    explicit AVLtree(int);
    ~AVLtree();

    pAVLnode root;

    int insert(pAVLnode&, int);
    int delet(pAVLnode&, int);
    void show();

private:

    void LL(pAVLnode&);
    void RR(pAVLnode&);
    void LR(pAVLnode&);
    void RL(pAVLnode&);
    void preorder(pAVLnode&);
    void inorder(pAVLnode&);
    void pBF(pAVLnode&);


    pAVLnode& getRightMost(pAVLnode&);
    pAVLnode& getLeftMost(pAVLnode&);

};