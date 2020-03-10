#include<malloc.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;
#if 0
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

struct BtNode* CreateTree3(const char** const pstr)
{
	struct BtNode* s = NULL;
	if (NULL != pstr && NULL != *pstr && **pstr != END)
	{
		s = Buynode();
		s->data = **pstr;
		++* pstr;
		s->leftchild = CreateTree3(pstr);
		// s->leftchild = CreateTree3(&++*pstr);
		++* pstr;
		s->rightchild = CreateTree3(pstr);
	}
	return s;
}

/*
****************************
     输出第K层的结点
****************************
*/
void PrintK(struct BtNode* ptr, int k)
{
    if (ptr != NULL && k == 0)
    {
        cout << ptr->data << " ";
    }
    else if (ptr != NULL)
    {
        PrintK(ptr->leftchild, k - 1); 
        PrintK(ptr->rightchild, k - 1);
    }
}
void Print_KLevel_Item(struct BtNode* ptr, int k)
{
    if (NULL == ptr || k < 0) return;
    PrintK(ptr, k);
    cout << endl;
}

/*
****************************
     获得二叉树结点个数
****************************
*/
int GetSize(struct BtNode* ptr)
{
	if (ptr == NULL) return 0;
	else return GetSize(ptr->leftchild) + GetSize(ptr->rightchild) + 1;
}

/*
****************************
     获得二叉树的深度
****************************
*/
int GetDepth(struct BtNode* ptr)
{
	if (ptr == NULL) return 0;
	else return max(GetDepth(ptr->leftchild), GetDepth(ptr->rightchild)) + 1;
}
int main()
{
	const char* str = "ABC##DE##F##G#H##";
	BinaryTree root = NULL;// 
	root = CreateTree3(&str); 

   //层次遍历
    int k = 0;
	int h = GetDepth(root);
    while (k < h)
    {
		Print_KLevel_Item(root, k);
		++k;
    }
	return 0;
}
#endif