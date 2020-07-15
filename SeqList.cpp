#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"SeqList.h"



//初始化操作
void InitSeq(SqList ps)
{
	//判空
	assert(ps != NULL);
	if (ps == NULL)
	{
		return;
	}
	//开辟length大小的格子
	ps->elem = (int*)malloc(sizeof(int) * SIZE);
	ps->size = 0;
	ps->length = SIZE;
}

//判满
static bool IsFull(SqList ps)
{
	return ps->length == ps->size;
}

//扩容
static void Resize(SqList ps)
{
	ps->elem = (int*)realloc(ps->elem, sizeof(int) * ps->size * 2);
	ps->length *= 2;
}
//指定位置插入数据
bool InsertSeq(SqList ps, int pos, int val)
{
	//判空
	assert(ps != NULL);
	if (ps == NULL)
	{
		return false;
	}

	//判断插入位置是否合法
	if (pos < 0 || pos > ps->size)
	{
		return false;
	}

	//判满，如果满了要扩容
	if (IsFull(ps))
	{
		Resize(ps);
	}

	//后移插入
	for (int i = ps->size - 1; i >= pos; i--)
	{
		ps->elem[i + 1] = ps->elem[i];
	}
	//更新有效元素个数
	ps->elem[pos] = val;
	ps->size ++ ;
	return true;
}

//按元素查找下标
int Search(SqList ps, int key)
{
	//判空
	assert(ps != NULL);
	if (ps == NULL)
		return -1;

	//循环顺序查找
	for (int i = 0; i < ps->size; i++)
	{
		if (ps->elem[i] == key)
		{
			return i;
		}
	}
	return -1;
}

//删除pos位置的值
bool DeletePos(SqList ps, int pos)
{
	//判空
	assert(ps != NULL);
	if (ps == NULL)
	{
		return false;
	}

	//判断pos位置是否合法
	if (pos < 0 || pos > ps->size)
	{
		return false;
	}

	//循环操作，前移删除
	for (int i = pos; i < ps->size - 1; i++)
	{
		ps->elem[i] = ps->elem[i + 1];
	}

	//更新size的大小
	ps->size -= 1;
	return true;
}

//删除key
bool DeleteVal(SqList ps, int key)
{
	//判空
	assert(ps != NULL);
	if (ps == NULL)
	{
		return false;
	}

	//查找元素，返回要删除元素的下标
	int pos = Search(ps, key);
	//删除
	return DeletePos(ps, pos);
}

//销毁
void Destroy(SqList ps)
{
	//判空
	assert(ps != NULL);
	//内存释放
	free(ps->elem);
	//其他成员重新初始化
	ps->elem = NULL;
	ps->size = 0;
	ps->length = 0;
}

//打印函数
void show(SqList ps)
{
	for (int i = 0; i < ps->size; i++)
	{
		printf("%d", ps->elem[i]);
	}
	printf("\n");
}

