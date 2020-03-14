#include<malloc.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<stack>
#include<algorithm>
#include<queue>
using namespace std;

#if 0
typedef int ElemType;
#define END -1
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
/*
***************************************
    二叉树的递归中序遍历（数组存放）
***************************************
*/
void Inorder(ElemType* br, int i, int n)
{
	if (i < n && br[i] != END)
	{
		Inorder(br, 2 * i + 1, n);
		cout << br[i]<<" ";
		Inorder(br, 2 * i + 2, n);
	}
}
void Inorder_Ar(ElemType* br, int n)
{
	if (NULL == br|| n < 1)return;
	Inorder(br, 0, n);
}
/*
***************************************
	二叉树的非递归中序遍历（数组存放）
***************************************
*/
void NiceInOrder(ElemType* br, int n)
{
	if (NULL == br || n<1) return;
	stack<int> st;//栈里面存放的是数组下标，所以是int
	int i = 0;//root
	while (!st.empty() || i<n)
	{
		while (i<n && br[i] != END)//i<n为了防止数组越界
		{
			st.push(i);
			i = i*2+1;
		}
		i = st.top(); st.pop();
		cout << br[i] << " ";
		i = i*2+2;
	}
	cout << endl;
}

/*
***************************************
	由顺序存储构造链式二叉树
***************************************
*/
struct BtNode* Create(ElemType* br,int i, int n)
{
	struct BtNode* s = NULL;
	if (i < n && br[i] != END)
	{
		s = Buynode();
		s->data = br[i];
		s->leftchild = Create(br, i * 2 + 1,n);
		s->rightchild = Create(br, i * 2 + 2, n);
	}
	return s;
}
struct BtNode* CreateAr(ElemType* br, int n)
{
	struct BtNode* s = NULL;
	if (br != NULL && n > 0)
	{
		s = Create(br, 0, n);
	}
	return s;
}

/*
***************************************
	由链式存储构造顺序存储二叉树
***************************************
*/
void LinkCreate_Ar(struct BtNode* p, ElemType* br, int i)
{
	if (p != NULL)
	{
		br[i] = p->data;
		LinkCreate_Ar(p->leftchild, br, 2 * i + 1);
		LinkCreate_Ar(p->rightchild, br, 2 * i + 2);
	}
}

/*
*******************************************************
	堆排序中的向下调整法:最小堆
	前提是下面的小堆以及调整完毕，现调整最大的堆
*******************************************************
*/
void FilterDown(int* br, int begin, int end)
{
	int i = begin, j = 2 * i + 1;
	int tmp = br[i];
	while (j <= end)
	{
		if (j<end &&br[j] > br[j + 1])++j;
		if (tmp <= br[j])break;
		br[i] = br[j];
		i = j;
		j = i * 2 + 1;
	}
	br[i] = tmp;
}
void HeapSort(int* br, int n)
{
	if (NULL == br || n < 2)return;
	int end = n - 1;
	int pos = (end - 1) / 2;//最后一个分支结点
	while (pos >= 0)
	{
		FilterDown(br, pos, end);
		--pos;
	}//一次筛选出一个最小堆顶
	//再在剩余堆中筛选最小堆
	while (end > 0)
	{
		swap(br[0], br[end]);//将刚筛选出的最小堆放在数组的最后一位
		end = end-1;
		FilterDown(br, 0, end);
	}
}

/*
*******************************************************
      优先级队列
*******************************************************
*/

const int MAXSIZE = 100;
const int INCSIZE = 2;
template<class Type>
class PriQueue
{
	Type* data;
	int maxsize;
	int cursize;
	void FilterDown(int begin, int end)
	{
		int i = begin;
		int j = 2 * i + 1;
		Type tmp = data[i];
		while (j <= end)
		{
			if (j < end && data[j] > data[j + 1]) ++j;//兄弟结点中，左边大于右边
			if (data[j] >= tmp) break;//孩子结点大于父子结点，符合最小堆，退出
			//继续向下走
			data[i] = data[j];
			i = j;
			j = 2 * i + 1;
		}
		data[i] = tmp;
	}
	void FilterUp(int begin)//这里面的begin是插入数据的下标位置
	{
		int j = begin;
		int i = (j - 1) / 2;
		Type tmp = data[j];
		while (j > 0)
		{
			if (data[i] <= tmp) break;//孩子结点大于父子结点，符合最小堆，退出
			data[j] = data[i];
			j = i;
			i = (j - 1) / 2;
		}
		data[j] = tmp;
	}
	void Make_Heap()
	{
		int end = cursize - 1;
		int pos = (end - 1) / 2;//第一个非叶子结点
		while (pos >= 0)
		{
			FileterDown(pos, end);
			--pos;
		}
	}
public:
	//动态开辟空间，构造函数
	PriQueue():maxsize(MAXSIZE), cursize(0)
	{
		data = new Type[maxsize];
	}
	//带参的构造函数
	PriQueue(Type* ar, int n)
	{
		maxsize = n > MAXSIZE ? n : MAXSIZE;
		cursize = n;
		data = new Type[maxsize];
		/*建堆的方式一：
		for(int i =0;i<n;++i
		{
			Push(ar[i]);
		}
		*/
		//将数放进数组,但是此时并不是一个堆
		for (int i = 0; i < n; i++)
		{
			data[i] = ar[i];
		}
		//建堆的方式二：调用建堆函数
		Make_Heap();
	}
	//析构函数
	~PriQueue()
	{
		delete[]data;
		data = NULL;
		maxsize = 0;
		cursize = 0;
	}

	int Getsize() const { return cursize; }
	bool IsEmpty() const 
	{ 
		return Getsize() == 0;
	}
	const Type& GetFront() const
	{
		return data[0];
	}
	void pop()
	{
		data[0] = data[cursize - 1];//覆盖,用最后元素的下标覆盖
		--cursize;//要删除一个元素
		//调整
		FilterDown(0, cursize - 1);
	}
	void Push(const Type& x)
	{
		if (cursize >= maxsize) return;
		data[cursize] = x;
		FilterUp(cursize);
		++cursize;
	}
};
int main()
{/*
	int ar[] = { 31,23,12,66,-1,5,17,70,62,-1,-1,-1,88,-1,55 };
	int n = sizeof(ar) / sizeof(ar[0]);

	//递归中序遍历
	Inorder_Ar(ar, n);
	cout << endl;

	//非递归中序遍历
	NiceInOrder(ar, n);

	//数组创建链式二叉树
	BinaryTree root = NULL;
	root = CreateAr(ar, n);

    //链式创建数组二叉树
	int br[] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
	LinkCreate_Ar(root, br,0);
	
	int ar1[] = { 53,17,78,9,45,65,87,23 };
	int n = sizeof(ar1) / sizeof(ar1[0]);
	HeapSort(ar1, n);*/
	
	PriQueue<int> pqu;
	int x;
	while (cin >> x, x != -1)
	{
		pqu.Push(x);
	}
	while (!pqu.IsEmpty())
	{
		int x = pqu.GetFront();
		pqu.pop();
		cout << x << endl;
	}
	return 0;
}
#endif