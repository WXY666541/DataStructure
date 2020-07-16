#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"SeqList.h"

int main()
{

	SeqList ps;
	InitSeq(&ps);
	for (int i = 0; i < 10; i++)
	{
		InsertSeq(&ps, i, i);
	}
	printf("插入0~9的数值：\n");
	show(&ps);
	printf("------------------\n");
	int pos = Search(&ps, 6);
	printf("查找6的位置为：%d\n", pos);
	printf("------------------\n");
	DeletePos(&ps, pos);
	printf("根据查找到6的位置删除该元素:\n");
	show(&ps);
	printf("------------------\n");
	DeleteVal(&ps, 3);
	printf("删除元素3：\n");
	show(&ps);
	printf("------------------\n");
	Destroy(&ps);
	printf("销毁\n");
	Destroy(&ps);
	show(&ps);
	return 0;
}