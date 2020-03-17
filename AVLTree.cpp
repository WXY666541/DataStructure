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
     ����һ�����
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
    �ͷŽ��
************************
*/
void Freenode(struct AVLNodee* p)
{
    free(p);
}

/*
************************
    ����һ�ſ���
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
        ����ת
**********************************
*/
void RotateLeft(AVLTree* ptree,struct AVLNode * ptr)
{
    //������ת����
    struct AVLNode* newroot = ptr->rightchild;//�ؼ�����1
    newroot->parent = ptr->parent;//�ı�˫�״���1
    ptr->rightchild = newroot->leftchild;//�ؼ�����2
    //�ı�˫�ײ���
    if (newroot->leftchild != NULL)//��newroot���������н������
    {
        newroot->leftchild->parent = ptr;//�ı�˫�״���2
    }
    newroot->leftchild = ptr;//�ؼ�����3
    if (ptr == ptree->head->parent)//��ԭ����ptrָ������
    {
        //��ʱnewroot�ͳ����µ�root���
        ptree->head->parent = newroot;
    }
    else//�������ʱ
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
    ptr->parent = newroot;//�ı�˫�״���3
}
/*
**********************************
        �ҵ���ת
**********************************
*/
void RotateRight(AVLTree* ptree, struct AVLNode* ptr)
{
    struct AVLNode* newroot = ptr->leftchild;//�ؼ�����1
    newroot->parent = ptr->parent;//�ı���˫�ף���ptrΪroot���ʱ��
    ptr->leftchild = newroot->rightchild;//�ؼ�����2
    if (newroot->rightchild != NULL)
    {
        newroot->rightchild->parent = ptr;//�ı������������˫��
    }
    newroot->rightchild = ptr;//�ؼ�����3
    if (ptr == ptree->head->parent)//��ptr��Ϊroot���ʱ
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
    ptr->parent = newroot;//�ı�˫�׽��3
}
/*
**********************************
        ��˫��
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
        case -1://������ĵ�ΪFʱ
            ptr->balance = 1;//���������任����ƽ����Ϊ����
            leftsub->balance = 0;
            break;
        case 1://������ĵ�ΪGʱ
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
        ��˫��
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
        case -1://������ĵ�ΪGʱ
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
    bool tall = true;//�߶�û�б仯����Ҫ����
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
    int ar[] = { 12,23,34,45,56,89,90.100 };//����ô�С����Ķ�ά���鴴��һ�Ŷ�����
}