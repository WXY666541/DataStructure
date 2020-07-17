# include<stdio.h>
# include<stdlib.h>
# include<assert.h>
# include "list.h"

int main()
{
	Node plist;
	InitList(&plist);
	for (int i = 0; i < 10; i++)
	{
		Insert_Head(&plist, i);
	}
	printf("前插入0~9的数值：\n");
	show(&plist);
	printf("---------------\n");
	Destroy(&plist);
	Destroy(&plist);
	printf("销毁\n");
	show(&plist);
	for (int i = 0; i < 10; i++)
	{
		Insert_Tail(&plist, i);
	}
	printf("销毁后,后插入0~9的数值：\n");
	show(&plist);
	printf("---------------\n");
	Delete(&plist, 0);
	printf("删除元素0：\n");
	show(&plist);
	printf("---------------\n");
	Reverse(&plist);
	printf("逆置单链表：\n");
	show(&plist);
	printf("---------------\n");
}
