#include<malloc.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<vector>
#include<stack>
using namespace std;

typedef char ElemType;
#define END '#'
typedef struct BtNode
{
	struct BtNode* leftchild;
	struct BtNode* rightchild;
	ElemType data;
}BtNode, * BinaryTree;//һ���ǽ�����ͣ�һ���Ǹý���ָ������

/*
   ****************************
	 ����һ�����
   ****************************
*/
struct BtNode* Buynode()
{
	struct BtNode* s = (struct  BtNode*)malloc(sizeof(struct BtNode*));
	if (NULL == s) exit(1);
	memset(s, 0, sizeof(struct BtNode));
	return s;
}

/*
   ****************************
	 �ͷ�һ�����
   ****************************
*/
void Freenode(struct BtNode* p)
{
	free(p);
}

/*
   ****************************
	 �ݹ����򹹽�������
   ****************************
*/
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

/*
   ****************************
	 �ݹ����򹹽�������
   ****************************
*/
struct BtNode* CreaetTree2()
{
	struct BtNode* s = NULL;
	ElemType item;
	cin >> item;
	if (item != END)
	{
		s = Buynode();
		s->leftchild = CreaetTree2();
		s->data = item;
		s->rightchild = CreaetTree2();
	}
	return s;
}

/*
   ****************************
	 �ݹ���򹹽�������
   ****************************
*/
struct BtNode* CreaetTree3()
{
	struct BtNode* s = NULL;
	ElemType item;
	cin >> item;
	if (item != END)
	{
		s = Buynode();
		s->leftchild = CreaetTree3();
		s->rightchild = CreaetTree3();
		s->data = item;
	}
	return s;
}


/*
   ****************************
   �ݹ飺����ǰ�����򹹽�������
   ****************************
*/
int FindIndex(const ElemType* istr, int n, ElemType x)
{
	int pos = -1;
	for (int i = 0; i < n; i++)
	{
		if (istr[i] == x)
		{
			pos = i;
			break;
		}
	}
	return pos;
}
struct BtNode* CreatePI(const ElemType* pstr, const ElemType* istr, int n)
{
	struct BtNode* s = NULL;
	if (n > 0)
	{
		s = Buynode();
		s->data = *pstr;
		int pos = FindIndex(istr, n, *pstr);//������������ȥ����
		s->leftchild = CreatePI(pstr + 1, istr, pos);
		s->rightchild = CreatePI(pstr + 1 + pos, istr + 1 + pos, n - pos - 1);
	}
	return s;
}
struct BtNode* CreateTresPI(const ElemType* pstr, const ElemType* istr, int n)
{
	if (NULL == pstr || NULL == istr || n < 1) return NULL;
	return CreatePI(pstr, istr, n);
}
/*
***********************************
   �ݹ飺����������򹹽�������
***********************************
*/
int FindIndex1(const ElemType* istr, int n, ElemType x)
{
	int pos = -1;
	for (int i = 0; i < n; i++)
	{
		if (istr[i] == x)
		{
			pos = i;
			break;
		}
	}
	return pos;
}
struct BtNode* CreateIL(const ElemType* istr, const ElemType* lstr, int n)
{
	struct BtNode* s = NULL;
	if (n > 0)
	{
		s = Buynode();
		s->data = lstr[n - 1];
		int pos = FindIndex1(istr, n, lstr[n - 1]);//������������ȥ����
		if (pos == -1) exit(1);
		s->leftchild = CreateIL(istr, lstr, pos);
		s->rightchild = CreateIL(istr + 1 + pos, lstr + 1 + pos, n - pos - 1);
	}
	return s;
}
struct BtNode* CreateTresIL(const ElemType* istr, const ElemType* lstr, int n)
{
	if (NULL == lstr || NULL == istr || n < 1) return NULL;
	return CreateIL(lstr, istr, n);
}

/*
*************************************************
   �ǵݹ飺��������ǰ�򹹽�������//���д���
************************************************
*/
struct BtNode* NiceCreateTree(const char  *pstr, const char *istr, int n)
{
	stack<struct BtNode*> st;
	int i = 0, j = 0;
	struct BtNode* root = Buynode();
	root->data = pstr[0];
	st.push(root);
	for (i = 0; i < n; i++)
	{
		struct BtNode* s = Buynode();
		s->data = pstr[i];
		if (!st.empty())
		{
			st.top()->leftchild = s;
		}
		st.push(s);
		struct BtNode* tmp = NULL;
		while (!st.empty() && st.top()->data == istr[j])
		{
			tmp = st.top();
			st.pop();
			++j;
		}
		if (tmp != NULL  && i < n)
		{
			struct BtNode* s = Buynode();
			s->data = pstr[++i];
			tmp->rightchild = s;
			st.push(s);
		}
	}
	return root;
}
int main()
{
	const char* pstr = "ABCDEFGH";
	const char* istr = "CBEDFAGH";
	const char* lstr = "CEFDBHGA";
	BinaryTree root = NULL;
	int n = strlen(pstr);

	root = NiceCreateTree(pstr, istr, n);

	root = CreateTresPI(pstr, istr, n);
	root = CreateTresIL(istr, lstr, n);
	return 0;
}
