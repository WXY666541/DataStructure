#include<iostream>
template <typename T>

class CLink;
template <typename T>
class Node
{
public:
	//构造函数可以不用加模板类型参数
	Node(T val = T())
		:mdata(val),pnext(NULL)
	{}
private:
	T mdata;
	Node<T>* pnext;
	friend class CLink<T>;
};

template <typename T>
class CLink
{
public:
	CLink();
	~CLink();

	void InsertHead(T val);
	void InsertTail(T val);
	bool Empty();
	void Destory();
	void show();
private:
	Node<T>* phead;
};


template <typename T>
CLink<T>::CLink()
{
	phead = new Node<T>();
}


template <typename T>
CLink<T>::~CLink()
{
	Node<T>* pcur = phead;
	Node<T>* pnext ;
	while (pcur != NULL)
	{
		pnext = pcur->pnext;
		delete pcur;
		pcur = pnext;
	}
	phead = NULL;
}

template <typename T>
void CLink<T>::InsertHead(T val)
{
	Node<T>* pnewnode = new Node<T>(val);

	pnewnode->pnext = phead->pnext;
	phead->pnext = pnewnode;
}

template <typename T>
void CLink<T>::InsertTail(T val)
{
	Node<T>* pnewnode = new Node<T>(val);
	Node<T>* ptail;
	
	for (ptail = phead; ptail->pnext != NULL; ptail = ptail->pnext);
	ptail->pnext = pnewnode;
	pnewnode->pnext = NULL;
}

template <typename T>
bool CLink<T>::Empty()
{
	return phead->pnext == NULL;
}

template <typename T>
void CLink<T>::Destory()
{
	if (Empty())
	{
		return ;
	}
	Node<T>* q;
	while (phead->pnext != NULL)
	{
		q = phead->pnext;
		phead->pnext = q->pnext;
		delete q;
	}
}

template <typename T>
void CLink<T>::show()
{
	Node<T>* q ;
	for (q = phead->pnext; q != NULL; q = q->pnext)
	{
		std::cout << q->mdata << " ";
	}
	std::cout << std::endl;
}

int main()
{
	CLink<double> cl;
	for (int i = 0; i < 5; i++)
	{
		cl.InsertHead(0.5 + i);
	}
	cl.show();
	for (int i = 0; i < 5; i++)
	{
		cl.InsertTail(0.5 + i);
	}
	cl.show();
	cl.Destory();
	cl.show();
	return 0;
}