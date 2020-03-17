#include<iostream>
#include<assert.h>
using namespace std;
typedef int KeyType;
typedef struct AVLNode
{
    struct AVLNode* leftchild;
    struct AVLNode* rightchild;
    struct AVLNode* parent;
    int balance;//-1 0 1
    KeyType key;
}AVLNode;
typedef struct
{
    AVLNode* head;
    int cursize;
}AVLTree;
/*
************************
     购买一个结点
************************
*/
struct AVLNode* Buynode()
{
    struct AVLNode* s = (struct AVLNode*)malloc(sizeof(struct AVLNode));
    if (NULL == s)exit(EXIT_FAILURE);
    memset(s, 0, sizeof(struct AVLNode));
    return s;
}

/*
************************
    释放结点
************************
*/
void Freenode(struct AVLNodee* p)
{
    free(p);
}

/*
************************
    建立一颗空树
************************
*/
void Init_AVLTree(AVLTree* ptree)
{
    assert(ptree != NULL);
    ptree->cursize = 0;
    ptree->head = Buynode();
}
/*
**********************************
        左单旋转
**********************************
*/
void RotateLeft(AVLTree* ptree,struct AVLNode * ptr)
{
    //三步旋转操作
    struct AVLNode* newroot = ptr->rightchild;//关键步骤1
    newroot->parent = ptr->parent;//改变双亲代码1
    ptr->rightchild = newroot->leftchild;//关键步骤2
    //改变双亲操作
    if (newroot->leftchild != NULL)//当newroot的左子树有结点的情况
    {
        newroot->leftchild->parent = ptr;//改变双亲代码2
    }
    newroot->leftchild = ptr;//关键步骤3
    if (ptr == ptree->head->parent)//当原来的ptr指向根结点
    {
        //此时newroot就成了新的root结点
        ptree->head->parent = newroot;
    }
    else//如果不是时
    {
        if (ptr == ptr->parent->leftchild)
        {
            ptr->parent->leftchild = newroot;
        }
        else
        {
            ptr->parent->rightchild = newroot;
        }
    }
    ptr->parent = newroot;//改变双亲代码3
}
/*
**********************************
        右单旋转
**********************************
*/
void RotateRight(AVLTree* ptree, struct AVLNode* ptr)
{
    struct AVLNode* newroot = ptr->leftchild;//关键步骤1
    newroot->parent = ptr->parent;//改变结点双亲（当ptr为root结点时）
    ptr->leftchild = newroot->rightchild;//关键步骤2
    if (newroot->rightchild != NULL)
    {
        newroot->rightchild->parent = ptr;//改变插入结点右子树双亲
    }
    newroot->rightchild = ptr;//关键步骤3
    if (ptr == ptree->head->parent)//当ptr就为root结点时
    {
        ptree->head->parent = newroot;
    }
    else
    {
        if (ptr == ptr->parent->rightchild)
        {
            ptr->parent->rightchild = newroot;
        }
        else
        {
            ptr->parent->leftchild = newroot;
        }
    }
    ptr->parent = newroot;//改变双亲结点3
}
/*
**********************************
        左双旋
**********************************
*/
void LeftBalance(AVLTree* ptree, struct AVLNode* ptr)
{
    struct AVLNode* leftsub = ptr->leftchild, * rightsub = NULL;
    switch (leftsub->balance)
    {
    case 0: cout << "Left Balance" << endl; break;
    case -1:
        ptr->balance = 0;
        leftsub->balance = 0;
        RotateLeft(ptree, ptr);
        break;
    case 1:
        rightsub = leftsub->rightchild;
        switch (rightsub->balance)
        {
        case -1://当插入的点为F时
            ptr->balance = 1;//经过调整变换过后平衡数为多少
            leftsub->balance = 0;
            break;
        case 1://当插入的点为G时
            ptr->balance = 0;
            leftsub->balance = -1;
            break;
        case 0:
            ptr->balance = 0;
            leftsub->balance = 0;
            break;
        }
        rightsub->balance = 0;
        RotateLeft(ptree, leftsub);
        RotateRight(ptree, ptr);
        break;
    }
}
/*
**********************************
        右双旋
**********************************
*/
void RightBalance(AVLTree* ptree, struct AVLNode* ptr)
{
    struct AVLNode* rightsub = ptr->rightchild, * leftsub = NULL;
    switch (rightsub->balance)
    {
    case 0: cout << "Right Balance" << endl; break;
    case 1:
        ptr->balance = 0;
        rightsub->balance = 0;
        RotateLeft(ptree, ptr);
        break;
    case -1:
        leftsub = rightsub->leftchild;
        switch (leftsub->balance)
        {
        case 1:
            ptr->balance = -1;
            rightsub->balance = 0;
            break;
        case -1://当插入的点为G时
            ptr->balance = 0;
            rightsub->balance = -1;
            break;
        case 0:
            ptr->balance = 0;
            rightsub->balance = 0;
            break;
        }
        leftsub->balance = 0;
        RotateRight(ptree,rightsub);
        RotateLeft(ptree, ptr);
        break;
    }
}
void Adjust_Tree(AVLTree* ptree, struct AVLNode* ptr)
{
    struct AVLNode* pa = ptr->parent;
    bool tall = true;//高度没有变化则不需要调整
    for (; tall && pa != ptree->head;)
    {
        if (pa->leftchild == ptr)
        {
            switch (pa->balance)
            {
            case 0: pa->balance = -1; break;
            case 1: pa->balance = 0; tall = false; break;
            case -1:
                LeftBalance(ptree, pa);
                tall = false;
                break;
            }
        }
        else
        {
            switch (pa->balance)
            {
            case 0: pa->balance = 1; break;
            case -1: pa->balance = 0; tall = false; break;
            case 1:
                RightBalance(ptree, pa);
                tall = false;
                break;
            }
        }
        ptr = pa;
        pa = ptr->parent;
    }
}
bool Insert(AVLTree* ptree, KeyType kx)
{
    if (ptree->head->parent == NULL)
    {
        struct AVLNode* root = Buynode();
        root->key = kx;
        ptree->head->parent = root;
        ptree->head->leftchild = root;
        ptree->head->rightchild = root;
        root->parent = ptree->head;
        ptree->cursize += 1;
        return true;
    }
    struct AVLNode* pa = ptree->head;       // head
    struct AVLNode* p = ptree->head->parent; // root;
    while (p != NULL && p->key != kx)
    {
        pa = p;
        p = kx < p->key ? p->leftchild : p->rightchild;
    }
    if (p != NULL && p->key == kx) return false;
    p = Buynode();
    p->key = kx;
    p->parent = pa;
    if (p->key < pa->key)
    {
        pa->leftchild = p;
        if (p->key < ptree->head->leftchild->key)
        {
            ptree->head->leftchild = p;
        }
    }
    else
    {
        pa->rightchild = p;
        if (p->key > ptree->head->rightchild->key)
        {
            ptree->head->rightchild = p;
        }
    }
    ptree->cursize += 1;
    Adjust_Tree(ptree, p);
    return true;
}

int main()
{
    int ar[] = { 12,23,34,45,56,89,90.100 };//如何用从小到达的二维数组创建一颗二叉树
}