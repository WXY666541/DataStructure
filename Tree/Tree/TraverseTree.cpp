#include<malloc.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<vector>
#include<stack>
#include<queue>
using namespace std;


typedef char ElemType;
#define END '#'
typedef struct BtNode
{
	struct BtNode* leftchild;
	struct BtNode* rightchild;
	ElemType data;
}BtNode, * BinaryTree;//一个是结点类型，一个是该结点的指针类型

struct BtNode* Buynode()
{
	struct BtNode* s = (struct  BtNode*)malloc(sizeof(struct BtNode*));
	if (NULL == s) exit(1);
	memset(s, 0, sizeof(struct BtNode));
	return s;
}
/*
   ****************************
	 递归遍历
   ****************************
*/
void PreOrder(struct BtNode* p)
{
	if (p != NULL)
	{
		printf("%c ", p->data);
		PreOrder(p->leftchild);
		PreOrder(p->rightchild);
	}
}
void InOrder(struct BtNode* p)
{
	if (p != NULL)
	{
		InOrder(p->leftchild);
		printf("%c ", p->data);
		InOrder(p->rightchild);
	}
}

void PastOrder(struct BtNode* p)
{
	if (p != NULL)
	{
		PastOrder(p->leftchild);
		PastOrder(p->rightchild);
		printf("%c ", p->data);
	}
}

/*
   ****************************
	 非递归中序遍历
   ****************************
*/
void NiceInOrder(struct BtNode* ptr)
{
	if (NULL == ptr) return;
	stack<struct BtNode*> st;
	while (!st.empty() || ptr != NULL)
	{
		while (ptr != NULL)
		{
			st.push(ptr);
			ptr = ptr->leftchild;
		}
		ptr = st.top(); st.pop();
		cout << ptr->data << " ";
		ptr = ptr->rightchild;
	}
	cout << endl;
}
/*
****************************
	 非递归后序遍历
****************************
*/
void NicePastOrder(struct BtNode* ptr)
{
	if (NULL == ptr) return;
	stack<struct BtNode*> st;
	struct BtNode* tag = NULL;
	while (!st.empty() || ptr != NULL)
	{
		while (ptr != NULL)
		{
			st.push(ptr);
			ptr = ptr->leftchild;
		}
		ptr = st.top(); st.pop();
		if (ptr->rightchild == NULL || ptr->rightchild == tag)
		{
			cout << ptr->data << " ";
			tag = ptr;
			ptr = NULL;
		}
		else
		{
			st.push(ptr);
			ptr = ptr->rightchild;
		}
	}
	cout << endl;
}
/*
****************************
	 非递归先序遍历
****************************
*/
void NicePreOrder(struct BtNode* ptr)
{
	if (ptr == NULL) return;
	stack<struct BtNode*> st;
	st.push(ptr);
	while (!st.empty())
	{
		ptr = st.top(); st.pop();
		cout << ptr->data << " ";
		if (ptr->rightchild != NULL)
		{
			st.push(ptr->rightchild);
		}
		if (ptr->leftchild != NULL)
		{
			st.push(ptr->leftchild);
		}
	}
	cout << endl;
}

/*
****************************
	 非递归后序遍历：利用栈
****************************
*/
struct StkNode
{
	struct BtNode* pnode;
	int popnum;
public:
	StkNode(struct BtNode* p = NULL) :pnode(p), popnum(0) {}
};
void StkNicePastOrder(struct BtNode* ptr)
{
	if (ptr == NULL) return;
	stack<StkNode> st;
	st.push(StkNode(ptr));
	while (!st.empty())
	{
		StkNode node = st.top(); st.pop();
		if (++node.popnum == 3)
		{
			cout << node.pnode->data << " ";
		}
		else
		{
			st.push(node);
			if (node.popnum == 1 && node.pnode->leftchild != NULL)
			{
				st.push(StkNode(node.pnode->leftchild));
			}
			else if (node.popnum == 2 && node.pnode->rightchild != NULL)
			{
				st.push(StkNode(node.pnode->rightchild));
			}
		}
	}
	cout << endl;
}

/*
****************************
	 非递归中序遍历：利用栈
****************************
*/
void StkNiceInOrder(struct BtNode* ptr)
{
	if (ptr == NULL) return;
	stack<StkNode> st;
	st.push(StkNode(ptr));
	while (!st.empty())
	{
		StkNode node = st.top(); st.pop();
		if (++node.popnum == 2)
		{
			cout << node.pnode->data << " ";	
		    if (node.pnode->rightchild != NULL)
			{
				st.push(StkNode(node.pnode->rightchild));
			}
		}
		else
		{
			st.push(node);
			if (node.popnum == 1 && node.pnode->leftchild != NULL)
			{
				st.push(StkNode(node.pnode->leftchild));
			}
		
		}
	}
	cout << endl;
}

/*
****************************
	 层次遍历：队列实现
根结点入队，队列不为空就打印
再依次入队左右节点
****************************
*/
void LevelOrder(struct BtNode* ptr)
{
	if (NULL == ptr) return;
	queue<struct BtNode*> qu;
	qu.push(ptr);
	while (!qu.empty())
	{
		ptr = qu.front(); qu.pop();
		cout << ptr->data << " ";
		if (ptr->leftchild != NULL)
		{
			qu.push(ptr->leftchild);
		}
		if (ptr->rightchild != NULL)
		{
			qu.push(ptr->rightchild);
		}
	}
	cout << endl;
}

/*
************************************
	 "工"字型遍历：两个队列实现
************************************
*/
void LevelOrder2(struct BtNode* ptr)
{
	if (NULL == ptr) return;
	stack<struct BtNode*> qua;
	queue<struct BtNode*> qub;
	qua.push(ptr);
	while (!qua.empty() || !qub.empty())
	{
		while(!qua.empty())
		{   ptr = qua.top(); qua.pop();
			cout << ptr->data << " ";
			if (ptr->rightchild != NULL)
			{
				qub.push(ptr->rightchild);
			}
			if (ptr->leftchild != NULL)
			{
				qub.push(ptr->leftchild);
			}
		}
		while (!qub.empty())
		{
			ptr = qub.front(); qub.pop();
			cout << ptr->data << " ";
			if (ptr->rightchild != NULL)
			{
				qua.push(ptr->rightchild);
			}
			if (ptr->leftchild != NULL)
			{
				qua.push(ptr->leftchild);
			}
		}
	}
	cout << endl;
}

struct BtNode* CreaetTree1()
{
	struct BtNode* s = NULL;
	ElemType item;
	cin >> item;
	if (item != END)
	{
		s = Buynode();
		s->data = item;
		s->leftchild = CreaetTree1();
		s->rightchild = CreaetTree1();
	}
	return s;
}

int main()
{
	BinaryTree root = NULL;
	root = CreaetTree1();
	LevelOrder2(root);
	LevelOrder(root);
	return 0;
}
