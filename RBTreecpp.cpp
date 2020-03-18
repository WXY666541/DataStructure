#include<iostream>
#include<assert.h>
#include<malloc.h>
using namespace std;
//�������
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
    struct rb_node* Nil;//�ڱ����
    int cursize;
}RBTree;
/*
************************
     ����һ�����
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
    �ͷŽ��
************************
*/
void Freenode(struct rb_nodee* p)
{
    free(p);
}

/*
************************
    ��ʼ��һ�ź����
************************
*/
void Init_RBTree(RBTree* ptree)
{
    assert(ptree != NULL);
    ptree->cursize = 0;
    ptree->Nil= Buynode(NULL,BLACK);//��ʼ�����ڱ����
    ptree->head = Buynode(ptree->Nil,RED);//��ʼ����ͷ���
    ptree->head->leftchild = ptree->head->rightchild = ptree->Nil;
}
/*
**********************************
        ����ת
**********************************
*/
void RotateLeft(RBTree* ptree, struct rb_node* ptr)
{
    //������ת����
    struct rb_node* newroot = ptr->rightchild;//�ؼ�����1
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
void RotateRight(RBTree* ptree, struct rb_node* ptr)
{
    struct rb_node* newroot = ptr->leftchild;//�ؼ�����1
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
        ����
**********************************
*/
void Adjust_Tree(RBTree* ptree, struct rb_node* ptr)
{
    struct rb_node* _X = ptr;//������
    struct rb_node* _Y = NULL;
    for (; _X != ptree->head->parent && _X->parent->color == RED;)//_X����head����Ҫ����
    {
        if (_X->parent == _X->parent->parent->rightchild)//˵���ڽ����ұ߲���
        {
            _Y = _X->parent->parent->leftchild;//ȷ��_Y����λ��
            if (_Y->color == RED)//���_YΪ��ɫ����ֻ��Ҫ��ɫ����
            {
                _Y->color = BLACK;
                _X->parent->color = BLACK;
                _X->parent->parent->color = RED;
                _X = _X->parent->parent;//��Ϊ����_X˫�׵�˫�׵�˫��Ϊ��ɫ�����������Ҫ����
            }
            else//���_YΪ��ɫ������Ҫ��ת����
            {
                if (_X == _X->parent->leftchild)//ֻ��������ת�����
                {
                    _X = _X->parent;
                    RotateRight(ptree, _X);
                }
                _X->parent->color = BLACK;
                _X->parent->parent->color = RED;
                RotateLeft(ptree, _X->parent->parent);//˫������
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
        ����һ�����
**********************************
*/
bool Insert(RBTree* ptree, KeyType kx)
{
    //���ҹ���
    struct rb_node* pa = ptree->head;       // head
    struct rb_node* p = ptree->head->parent; // root;
    while (p != ptree->Nil && p->key != kx)
    {
        pa = p;
        p = kx < p->key ? p->leftchild : p->rightchild;
    }
    if (p != ptree->Nil && p->key == kx) return false;
    p = Buynode(pa,RED);//����ÿһ������ʱ��Ϊ��ɫ�����˸��Ǻ�ɫ
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
        if (p->key < pa->key)//���
    {
        pa->leftchild = p;
        if (p->key < ptree->head->leftchild->key)
        {
            ptree->head->leftchild = p;
        }
    }
    else//�ұ�
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
 �������еĽ�㣨ѭ����
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
  �������еĽ�㣨�ݹ飩
************************
*/

struct rb_node* Search(RBTree * ptree,struct rb_node* ptr, KeyType kx)
{
    if (ptr == ptree->Nil) return NULL;//�����ڱ�λ
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
    �������
************************
*/

//����������ĵ�һ���ڵ�
struct rb_node* First(RBTree* ptree,struct rb_node* ptr)
{

    while (ptr != ptree->Nil && ptr->leftchild != ptree->Nil)
    {
        ptr = ptr->leftchild;
    }
    return ptr;
}
//����������ĵ�һ���ڵ�ĺ��
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
    ������������
************************
*/

//�����һ�����
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
    �ж��Ƿ�ΪBST��
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


