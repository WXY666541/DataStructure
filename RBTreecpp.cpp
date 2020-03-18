#include<iostream>
#include<assert.h>
#include<malloc.h>
using namespace std;
//结点类型
typedef enum{RED = 0,BLACK = 1}ColorType;
typedef int KeyType;
typedef struct rb_node
{
    struct rb_node* leftchild;
    struct rb_node* rightchild;
    struct rb_node* parent;
    ColorType color;
    KeyType key;
}rb_node;
typedef struct
{
    rb_node* head;
    struct rb_node* Nil;//哨兵结点
    int cursize;
}RBTree;
/*
************************
     购买一个结点
************************
*/
struct rb_node* Buynode(struct rb_node *pa,ColorType color)
{
    struct rb_node* s = (struct rb_node*)malloc(sizeof(struct rb_node));
    if (NULL == s)exit(EXIT_FAILURE);
    memset(s, 0, sizeof(struct rb_node));
    return s;
}

/*
************************
    释放结点
************************
*/
void Freenode(struct rb_nodee* p)
{
    free(p);
}

/*
************************
    初始化一颗红黑树
************************
*/
void Init_RBTree(RBTree* ptree)
{
    assert(ptree != NULL);
    ptree->cursize = 0;
    ptree->Nil= Buynode(NULL,BLACK);//初始化的哨兵结点
    ptree->head = Buynode(ptree->Nil,RED);//初始化的头结点
    ptree->head->leftchild = ptree->head->rightchild = ptree->Nil;
}
/*
**********************************
        左单旋转
**********************************
*/
void RotateLeft(RBTree* ptree, struct rb_node* ptr)
{
    //三步旋转操作
    struct rb_node* newroot = ptr->rightchild;//关键步骤1
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
void RotateRight(RBTree* ptree, struct rb_node* ptr)
{
    struct rb_node* newroot = ptr->leftchild;//关键步骤1
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
        调整
**********************************
*/
void Adjust_Tree(RBTree* ptree, struct rb_node* ptr)
{
    struct rb_node* _X = ptr;//插入结点
    struct rb_node* _Y = NULL;
    for (; _X != ptree->head->parent && _X->parent->color == RED;)//_X等于head不需要调整
    {
        if (_X->parent == _X->parent->parent->rightchild)//说明在结点的右边插入
        {
            _Y = _X->parent->parent->leftchild;//确定_Y结点的位置
            if (_Y->color == RED)//如果_Y为红色，则只需要颜色调整
            {
                _Y->color = BLACK;
                _X->parent->color = BLACK;
                _X->parent->parent->color = RED;
                _X = _X->parent->parent;//因为存在_X双亲的双亲的双亲为红色的情况，还需要调整
            }
            else//如果_Y为黑色，则需要旋转操作
            {
                if (_X == _X->parent->leftchild)//只进行右旋转的情况
                {
                    _X = _X->parent;
                    RotateRight(ptree, _X);
                }
                _X->parent->color = BLACK;
                _X->parent->parent->color = RED;
                RotateLeft(ptree, _X->parent->parent);//双旋操作
            }
        }
        else // left
        {
            _Y = _X->parent->parent->rightchild;
            if (_Y->color == RED)
            {
                _Y->color = BLACK;
                _X->parent->color = BLACK;
                _X->parent->parent->color = RED;
                _X = _X->parent->parent;
            }
            else
            {
                if (_X == _X->parent->rightchild)
                {
                    _X = _X->parent;
                    RotateLeft(ptree, _X);
                }
                _X->parent->color = BLACK;
                _X->parent->parent->color = RED;
                RotateRight(ptree, _X->parent->parent);
            }
        }
    }
    ptree->head->parent->color = BLACK;
}
/*
**********************************
        插入一个结点
**********************************
*/
bool Insert(RBTree* ptree, KeyType kx)
{
    //查找过程
    struct rb_node* pa = ptree->head;       // head
    struct rb_node* p = ptree->head->parent; // root;
    while (p != ptree->Nil && p->key != kx)
    {
        pa = p;
        p = kx < p->key ? p->leftchild : p->rightchild;
    }
    if (p != ptree->Nil && p->key == kx) return false;
    p = Buynode(pa,RED);//插入每一个结点的时候为红色，除了根是黑色
    p->key = kx;
    p->leftchild = p->rightchild = ptree->Nil;
    if (pa == ptree->head)
    {
        ptree->head->parent = p;
        ptree->head->leftchild = p;
        ptree->head->rightchild = p;
    }
    else
    {
        if (p->key < pa->key)//左边
    {
        pa->leftchild = p;
        if (p->key < ptree->head->leftchild->key)
        {
            ptree->head->leftchild = p;
        }
    }
    else//右边
    {
        pa->rightchild = p;
        if (p->key > ptree->head->rightchild->key)
        {
            ptree->head->rightchild = p;
        }
    }
    }
    ptree->cursize += 1;
    Adjust_Tree(ptree, p);
    return true;
}
/*
************************
 查找树中的结点（循环）
************************
*/
struct rb_node* FindValue(RBTree* ptree, KeyType val)
{
    if (ptree == NULL)return NULL;
    struct rb_node* p = ptree->head->parent;//root
    while (p != ptree->Nil && p->key != val)
    {
        p = val < p->key ? p->leftchild : p->rightchild;
    }
    if (p == ptree->Nil)
    {
        p = NULL;
    }
    return p;
}
/*
************************
  查找树中的结点（递归）
************************
*/

struct rb_node* Search(RBTree * ptree,struct rb_node* ptr, KeyType kx)
{
    if (ptr == ptree->Nil) return NULL;//到达哨兵位
    else if (ptr->key == kx) return ptr;
    else if (kx < ptr->key)
        return Search(ptree,ptr->leftchild, kx);
    else
        return Search(ptree,ptr->rightchild, kx);
}
struct rb_node* SearchValue(RBTree* ptree, KeyType kx)
{
    struct rb_node* p = NULL;
    if (ptree != NULL)
    {
        p = Search(ptree,ptree->head->parent, kx);
    }
    return p;
}
/*
************************
    中序遍历
************************
*/

//找中序遍历的第一个节点
struct rb_node* First(RBTree* ptree,struct rb_node* ptr)
{

    while (ptr != ptree->Nil && ptr->leftchild != ptree->Nil)
    {
        ptr = ptr->leftchild;
    }
    return ptr;
}
//找中序遍历的第一个节点的后继
struct rb_node* Next(RBTree* ptree, struct rb_node* ptr)
{
    if (ptr == NULL || ptr == ptree->Nil)return NULL;
    if (ptr->rightchild != ptree->Nil)
    {
        return First(ptree,ptr->rightchild);
    }
    else
    {
        struct rb_node* pa = ptr->parent;
        while (pa != ptree->head && ptr != pa->leftchild)
        {
            ptr = pa;
            pa = ptr->parent;
        }
        if (pa == ptree->head)
        {
            pa = NULL;
        }
        return pa;
    }
}
void NiceInOrder(RBTree* ptree)
{
    assert(ptree != NULL);
    for (struct rb_node* p = First(ptree,ptree->head->parent); p != NULL; p = Next(ptree, p))
    {
        cout << p->key << "  ";
    }
    cout << endl;
}

/*
************************
    中序的逆序遍历
************************
*/

//找最后一个结点
struct rb_node* Last(RBTree *ptree,struct rb_node* ptr)
{
    while (ptr != ptree->Nil && ptr->rightchild != ptree->Nil)
    {
        ptr = ptr->rightchild;
    }
    return ptr;
}
struct rb_node* Prev(RBTree* ptree, struct rb_node* ptr)
{
    if (ptr == NULL || ptr == ptree->Nil) return NULL;
    if (ptr->leftchild != NULL)
    {
        return Last(ptree,ptr->leftchild);
    }
    else
    {
        struct rb_node* pa = ptr->parent;
        while (pa != ptree->head && ptr != pa->rightchild)
        {
            ptr = pa;
            pa = ptr->parent;
        }
        if (pa == ptree->head)
        {
            pa = NULL;
        }
        return pa;
    }
}
void ResNiceInOrder(RBTree* ptree)
{
    assert(ptree != NULL);
    for (struct rb_node* p = Last(ptree,ptree->head->parent); p != NULL; p = Prev(ptree, p))
    {
        cout << p->key << "  ";
    }
    cout << endl;
}
/*
************************
    判断是否为BST树
************************
*/
bool Is_BSTree(RBTree* ptree)
{
    assert(ptree != NULL);
    bool res = true;
    struct rb_node* pre = NULL;
    for (struct rb_node* p = First(ptree, ptree->head->parent); p != NULL; p = Next(ptree, p))
    {
        if (pre == NULL)
        {
            pre = p;
        }
        else
        {
            if (pre->key > p->key)
            {
                res = false;
                break;
            }
            pre = p;
        }
    }
    return res;
}


