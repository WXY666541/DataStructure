#include<iostream>
using namespace std;

#define M 5
#define MAXSIZE (M-1)
#define MINSIZE (M/2)
typedef char KeyType;
typedef struct {}Record;
typedef struct
{
	KeyType key;
	Record* recptr;
}ElemType;
typedef struct BNode
{
	int num;
	struct BNode* parent;
	ElemType data[M + 1];
	struct BNode* sub[M + 1];
}BNode;
typedef struct
{
	struct BNode* root;
	int cursize;
}BTree;

//返回
typedef struct
{
	struct BNode* ptr;
	int index;
	bool tag;
}Result;
struct BNode* Buynode()
{
	struct BNode* s = (struct BNode*)malloc(sizeof(struct BNode));
	if (NULL == s)exit(EXIT_FAILURE);
	memset(s, 0, sizeof(struct BNode));
	return s;
}
void Init_BTree(BTree* ptree)
{
	ptree->root = NULL;
	ptree->cursize = 0;
}
Result FindValue(BTree* ptree, KeyType kx)
{
	Result res = { NULL,-1,false };
	if (ptree == NULL) return res;
	struct BNode* p = ptree->root;
	while (p != NULL)
	{
		int i = p->num;
		p->data[0].key = kx;
		while (kx < p->data[i].key) --i;
		res.ptr = p; res.index = i;
		if (i > 0 && p->data[i].key == kx)//找到了
		{
			res.tag = true;
			break;
		}
		p = p->sub[i];
	}
	return res;
}
Result Search(struct BNode* p, KeyType kx)
{
	Result res = { NULL,-1,false };
	if (p != NULL)
	{
		int i = p->num;
		p->data[0].key = kx;
		while (kx < p->data[i].key) --i;
		res.ptr = p; res.index = i;
		if (i > 0 && p->data[i].key == kx)//找到了
		{
			res.tag = true;
		}
		else if (p->sub[i] != NULL)
		{
			res = Search(p->sub[i], kx);
		}
	}
}
Result SearchValue(BTree* ptree, KeyType kx)
{
	Result res = { NULL,-1,false };
	if (ptree == NULL)
	{
		res = Search(ptree->root, kx);
	}
	
}
struct BNode* MakeRoot(ElemType item, struct BNode* left, struct BNode* right)
{
	struct BNode* s = Buynode();
	s->parent = NULL;
	s->num = 1;
	s->data[1] = item;
	s->sub[0] = left;
	if (left != NULL)left->parent = s;
	s->sub[1] = right;
	if (left != NULL)right->parent = s;
	return s;
}
void Insert_Item(struct BNode* ptr, int pos, ElemType item, struct BNode* right)
{
	for (int i = ptr->num; i > pos; --i)
	{
		ptr->data[i + 1] = ptr->data[i];
		ptr->sub[i + 1] = ptr->sub[i];
	}
	ptr->data[pos + 1] = item;
	ptr->sub[pos + 1] = right;
	if (right != NULL) right->parent = ptr;
	ptr->num += 1;
}
ElemType Move_Item(struct BNode* ptr,struct BNode *s,int index)
{
	for (int i = index, j = 0; i < ptr->num; ++i,++j)
	{
		s->data[j] = ptr->data[i];
		s->sub[j] = ptr->sub[i];
		if (s->sub[j] != NULL)s->sub[j]->parent = s;
	}
	ptr->num = MINSIZE;
	s->num = MINSIZE;
	s->parent = ptr->parent;
	return s->data[0];
}
struct BNode* Splice(struct BNode* ptr)
{
	struct BNode* newroot = NULL;
	struct BNode* s = Buynode();
	ElemType item = Move_Item(ptr, s, MINSIZE + 1);
	if (ptr->parent == NULL)
	{
		newroot= MakeRoot(item, ptr, s);
	}
	else
	{
		struct BNode* pa = ptr->parent;
		int pos = pa->num;
		pa->data[0] = item;
		while (item.key < pa->data[pos].key) --pos;
		Insert_Item(pa, pos, item, s);
		if (pa->num > MAXSIZE)
		{
			newroot = Splice(pa);
		}
	}
	return newroot;
}
bool Insert(BTree* ptree, ElemType item)
{
	if (ptree == NULL) return false;
	if (ptree->root == NULL)
	{
		ptree->root = MakeRoot(item, NULL, NULL);
		ptree->cursize = 1;
		return true;
	}
	Result res = FindValue(ptree, item.key);
	if (res.ptr == NULL || res.tag) return false;
	struct BNode* ptr = res.ptr;
	int pos = res.index;
	Insert_Item(ptr, pos, item, NULL);
	ptree->cursize += 1;
	if (ptr->num > MAXSIZE)
	{
		struct BNode* newroot = Splice(ptr);
		if (newroot != NULL)
		{
			ptree->root = newroot;
		}
	}
	return true;
}
int main()
{
	char ar[] = { "dsgerfwfjgdudgduygdjedjwdwnd" };
	int n = sizeof(ar) / sizeof(ar[0]) - 1;
	BTree myt;
	Init_BTree(&myt);
	for (int i = 0; i < n; i++)
	{
		ElemType item = { ar[i],NULL };
		Insert(&myt, item);
	}
	return 0;
}