#include<malloc.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
#include<queue>
using namespace std;

typedef char ElemType;
#define END '#'
typedef struct BtNode
{
	struct BtNode* leftchild;
	struct BtNode* rightchild;
	ElemType data;
}BtNode, * BinaryTree;

struct BtNode* Buynode()
{
	struct BtNode* s = (struct  BtNode*)malloc(sizeof(struct BtNode*));
	if (NULL == s) exit(1);
	memset(s, 0, sizeof(struct BtNode));
	return s;
}

struct BtNode* NiceCreateTree(const char* pstr, const char* istr, int n)
{
	stack<struct BtNode*> st;
	int i = 0, j = 0;
	struct BtNode* root = Buynode();
	root->data = pstr[0];
	st.push(root);
	for (i = 1; i < n; ++i)
	{
		struct BtNode* s = Buynode();
		s->data = pstr[i];
		if (!st.empty())
		{
			st.top()->leftchild = s;
		}
		st.push(s);
		struct BtNode* tmp = NULL;
		while (j < n && st.top()->data == istr[j])
		{
			while (!st.empty() && st.top()->data == istr[j])
			{
				tmp = st.top();
				st.pop();
				++j;
			}
			if (tmp != NULL && i < n - 1)
			{
				struct BtNode* s = Buynode();
				s->data = pstr[++i];
				tmp->rightchild = s;
				st.push(s);
			}
		}
	}
	return root;
}

int GetDepth(struct BtNode* ptr)
{
	if (ptr == NULL) return 0;
	else return max(GetDepth(ptr->leftchild), GetDepth(ptr->rightchild)) + 1;
}

/*
**********************************
	 ����ֵΪvalֵ��������ڷ���
	 ���ĵ�ַ�����򷵻�NULL
***********************************
*/
struct BtNode* FindValue(struct BtNode* ptr, ElemType val)
{
	if (ptr == NULL || ptr->data == val)
	{
		return ptr;
	}
	else
	{
		struct BtNode* p = FindValue(ptr->leftchild, val);
		if (NULL == p)
		{
			p = FindValue(ptr->rightchild, val);
		}
		return p;
	}
}

/*
*******************************************
	 �ҵ��ö�������ĳ��ָ���ڵ���˫��
*******************************************
*/
struct BtNode* Parent(struct BtNode* ptr, struct BtNode* child)
{
	if (ptr == NULL || ptr->leftchild == child || ptr->rightchild == child)//����һ�����Ƭ
	{
		return ptr;
	}
	else
	{
		struct BtNode* p = Parent(ptr->leftchild, child);
		if (NULL == p)
		{
			p = Parent(ptr->leftchild, child);
		}
		return p;
	}
}
struct BtNode* FindParent(struct BtNode* ptr, struct BtNode* child)
{
	if (NULL == ptr || NULL == child || ptr == child)//�������������
	{
		return NULL;
	}
	else
	{
		return Parent(ptr, child);
	}

}
/*
*****************************************************************************************
	 �ж��Ƿ�Ϊ��������:��������ʵ��
	 ����������������������ĸ߶����� 2^k+1 = ������
	 ��������������������������������ҲΪ�����������Ҹ߶���ͬ�����ᳫ��ʱ�临�Ӷ�̫�ߣ�
********************************************************************************************
*/
bool Is_Full_BinTree(struct BtNode* ptr)
{
	bool res = true;
	if (NULL == ptr)return res;
	queue<struct BtNode*> qua,qub;
	int n = 1;
	qua.push(ptr);
	while (!qua.empty() || !qub.empty())
	{
		int i = 0;
		if (qua.size() < n) { res = false; break; }
		while ( i < n)
		{
			struct BtNode* p = qua.front; qua.pop();
			if (p->leftchild != NULL)
			{
				qub.push(p->leftchild);
			}
			if (p->rightchild != NULL)
			{
				qub.push(p->rightchild);
			}
			++i;
		}
		n += n;
		i = 0;
		if (qub.size() < n) { res = false; break; }
		while ( i < n)
		{
			struct BtNode* p = qub.front; qub.pop();
			if (p->leftchild != NULL)
			{
				qua.push(p->leftchild);
			}
			if (p->rightchild != NULL)
			{
				qua.push(p->rightchild);
			}
			++i;
		}
	}
	return res;
}
bool Is_Full(struct BtNode* ptr)
{
	return (ptr == NULL || (Is_Full(ptr->leftchild) && Is_Full(ptr->rightchild) &&
		GetDepth(ptr->leftchild) == GetDepth(ptr->rightchild)));
}
/*
*******************************************
	 �ж��Ƿ�Ϊ��ȫ������
*******************************************
*/

int main()
{
	const char* pstr = "ABCDEFGH";
	const char* istr = "CBEDFAGH";
	const char* lstr = "CEFDBHGA";
	BinaryTree root = NULL;
	int n = strlen(pstr);
	root = NiceCreateTree(pstr, istr, n);
	char val;
	while (cin >> val, val != END)
	{
		struct BtNode* p = FindValue(root, val);
		if (p != NULL)
		{
			cout << p << " ==> " << p->data << endl;
		}
		else
		{
			cout << "not value" << endl;
		}
	}

	return 0;
}
