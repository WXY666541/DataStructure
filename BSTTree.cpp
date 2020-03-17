#include<iostream>
#include<assert.h>
#include<malloc.h>
using namespace std;
/*
*******************************************************
      二叉搜索树，三叉链表
      有两种结构：一种是结点类型
*******************************************************
*/
//结点类型
typedef int KeyType;
typedef struct BstNode
{
    struct BstNode* leftchild;
    struct BstNode* rightchild;
    struct BstNode* parent;
    KeyType key;
}BstNode;
typedef struct
{
    BstNode* head;
    int cursize;
}BSTree;
/*
************************
     购买一个结点
************************
*/
struct BstNode* Buynode()
{
    struct BstNode* s = (struct BstNode*)malloc(sizeof(struct BstNode));
    if (NULL == s)exit(EXIT_FAILURE);
    memset(s, 0, sizeof(struct BstNode));
    return s;
}

/*
************************
    释放结点
************************
*/
void Freenode(struct BstNode* p)
{
    free(p);
}

/*
************************
    建立一颗空树
************************
*/
void Init_BSTree(BSTree* ptree)
{
    assert(ptree != NULL);
    ptree->cursize = 0;
    ptree->head = Buynode();
}

/*
************************
 查找树中的结点（循环）
************************
*/

struct BstNode* FindValue(BSTree* ptree, KeyType val)
{
    if (ptree == NULL)return NULL;
    struct BstNode* p = ptree->head->parent;
    while (p != NULL && p->key != val)
    {
        p = val < p->key ? p->leftchild : p->rightchild;
    }
    return p;
}

/*
************************
  查找树中的结点（递归）
************************
*/

struct BstNode* Search(struct BstNode* ptr, KeyType kx)
{
    if (ptr == NULL || ptr->key == kx)
        return ptr;
    else if (kx < ptr->key)
        return Search(ptr->leftchild, kx);
    else
        return Search(ptr->rightchild, kx);
}
struct BstNode* SearchValue(BSTree* ptree, KeyType kx)
{
    struct BstNode* p = NULL;
    if (ptree != NULL)
    {
        p = Search(ptree->head->parent, kx);
    }
    return p;
}
/*
************************
    中序遍历
************************
*/

//找中序遍历的第一个节点
struct BstNode* First(struct BstNode* ptr)
{

    while (ptr != NULL && ptr->leftchild != NULL)
    {
        ptr = ptr->leftchild;
    }
    return ptr;
}
//找中序遍历的第一个节点的后继
struct BstNode* Next(BSTree *ptree,struct BstNode *ptr)
{
    if (ptr == NULL)return NULL;
    if (ptr->rightchild != NULL)
    {
        return First(ptr->rightchild);
    }
    else
    {
        struct BstNode* pa = ptr->parent;
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
void NiceInOrder(BSTree* ptree)
{
    assert(ptree != NULL);
    for (struct BstNode* p = First(ptree->head->parent); p != NULL; p = Next(ptree, p))
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
struct BstNode* Last(struct BstNode* ptr)
{
    while (ptr != NULL && ptr->rightchild != NULL)
    {
        ptr = ptr->rightchild;
    }
    return ptr;
}
struct BstNode* Prev(BSTree* ptree, struct BstNode* ptr)
{
    if (ptr == NULL) return NULL;
    if (ptr->leftchild != NULL)
    {
        return Last(ptr->leftchild);
    }
    else
    {
        struct BstNode* pa = ptr->parent;
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
void ResNiceInOrder(BSTree* ptree)
{
    assert(ptree != NULL);
    for (struct BstNode* p = Last(ptree->head->parent); p != NULL; p = Prev(ptree, p))
    {
        cout << p->key << "  ";
    }
    cout << endl;
}

/*
************************
   构建二叉树
************************
*/

bool Insert(BSTree* ptree, KeyType kx)
{
    //空树的情况下插入一个头结点，相当于建立一个root结点
    if (ptree->head->parent == NULL)
    {
        struct BstNode* root = Buynode();
        root->key = kx;
        ptree->head->parent = root;
        ptree->head->leftchild = root;
        ptree->head->rightchild = root;
        root->parent = ptree->head;
        ptree->cursize += 1;
        return true;
    }
    struct BstNode* pa = ptree->head;       // head
    struct BstNode* p = ptree->head->parent; // root;
    //找结点应该插入的位置
    while (p != NULL && p->key != kx)
    {
        pa = p;
        p = kx < p->key ? p->leftchild : p->rightchild;
    }
    //没找到的情况
    if (p != NULL && p->key == kx) return false;
    //找到了执行插入操作
    p = Buynode();
    p->key = kx;
    p->parent = pa;
    //插入过程中并更新head结点的左右指向
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
    return true;
}
/*
************************
    删除一个结点，有以下四种情况
    1、叶子
    2、单分支
    3、双分支
    存在删除过后用什么替换的问题，要找删除结点和直接前驱或直接后继（不可能是双分支，只能是叶子或单分支）来替换
************************
*/
bool Remove(BSTree* ptree, KeyType kx)
{
    //没找到结点
    if (ptree->head->parent == NULL) return false;
    struct BstNode* p = FindValue(ptree, kx);
    if (p == NULL) return false;
    //找到了
    struct BstNode* pa = p->parent;
    //双分支的情况
    if (p->leftchild != NULL && p->rightchild != NULL)
    {
        struct BstNode* nt = Next(ptree, p);
        p->key = nt->key;
        p = nt;
    }
    //删除叶子结点和单分支的情况
    struct BstNode* child = p->leftchild != NULL ? p->leftchild : p->rightchild;
    if (child != NULL) child->parent = pa;
    //要删除的结点时root时(单根）
    if (pa == ptree->head)
    {
        pa->parent = p;
    }
    //其他单分支情况
    else
    {
        if (pa->leftchild == p)
        {
            pa->leftchild = child;
        }
        else
        {
            pa->rightchild = child;
        }
    }
    Freenode(p);
    ptree->cursize -= 1;
    return true;
}
int main()
{
    int ar[] = { 53,17,78,9,45,65,87,23,81,94,88,100 };
    int n = sizeof(ar) / sizeof(ar[0]);
    BSTree mytree;
    Init_BSTree(&mytree);
    for (int i = 0; i < n; ++i)
    {
        Insert(&mytree, ar[i]);
    }
    NiceInOrder(&mytree);
    ResNiceInOrder(&mytree);
    int kx;
    while (cin >> kx, kx != -1)
    {
        cout << Remove(&mytree, kx) << endl;
        NiceInOrder(&mytree);
    }
    return 0;
}