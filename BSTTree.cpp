#include<iostream>
#include<assert.h>
#include<malloc.h>
using namespace std;
/*
*******************************************************
      ��������������������
      �����ֽṹ��һ���ǽ������
*******************************************************
*/
//�������
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
     ����һ�����
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
    �ͷŽ��
************************
*/
void Freenode(struct BstNode* p)
{
    free(p);
}

/*
************************
    ����һ�ſ���
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
 �������еĽ�㣨ѭ����
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
  �������еĽ�㣨�ݹ飩
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
    �������
************************
*/

//����������ĵ�һ���ڵ�
struct BstNode* First(struct BstNode* ptr)
{

    while (ptr != NULL && ptr->leftchild != NULL)
    {
        ptr = ptr->leftchild;
    }
    return ptr;
}
//����������ĵ�һ���ڵ�ĺ��
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
    ������������
************************
*/

//�����һ�����
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
   ����������
************************
*/

bool Insert(BSTree* ptree, KeyType kx)
{
    //����������²���һ��ͷ��㣬�൱�ڽ���һ��root���
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
    //�ҽ��Ӧ�ò����λ��
    while (p != NULL && p->key != kx)
    {
        pa = p;
        p = kx < p->key ? p->leftchild : p->rightchild;
    }
    //û�ҵ������
    if (p != NULL && p->key == kx) return false;
    //�ҵ���ִ�в������
    p = Buynode();
    p->key = kx;
    p->parent = pa;
    //��������в�����head��������ָ��
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
    ɾ��һ����㣬�������������
    1��Ҷ��
    2������֧
    3��˫��֧
    ����ɾ��������ʲô�滻�����⣬Ҫ��ɾ������ֱ��ǰ����ֱ�Ӻ�̣���������˫��֧��ֻ����Ҷ�ӻ򵥷�֧�����滻
************************
*/
bool Remove(BSTree* ptree, KeyType kx)
{
    //û�ҵ����
    if (ptree->head->parent == NULL) return false;
    struct BstNode* p = FindValue(ptree, kx);
    if (p == NULL) return false;
    //�ҵ���
    struct BstNode* pa = p->parent;
    //˫��֧�����
    if (p->leftchild != NULL && p->rightchild != NULL)
    {
        struct BstNode* nt = Next(ptree, p);
        p->key = nt->key;
        p = nt;
    }
    //ɾ��Ҷ�ӽ��͵���֧�����
    struct BstNode* child = p->leftchild != NULL ? p->leftchild : p->rightchild;
    if (child != NULL) child->parent = pa;
    //Ҫɾ���Ľ��ʱrootʱ(������
    if (pa == ptree->head)
    {
        pa->parent = p;
    }
    //��������֧���
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