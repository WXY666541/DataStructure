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
	printf("ǰ����0~9����ֵ��\n");
	show(&plist);
	printf("---------------\n");
	Destroy(&plist);
	Destroy(&plist);
	printf("����\n");
	show(&plist);
	for (int i = 0; i < 10; i++)
	{
		Insert_Tail(&plist, i);
	}
	printf("���ٺ�,�����0~9����ֵ��\n");
	show(&plist);
	printf("---------------\n");
	Delete(&plist, 0);
	printf("ɾ��Ԫ��0��\n");
	show(&plist);
	printf("---------------\n");
	Reverse(&plist);
	printf("���õ�����\n");
	show(&plist);
	printf("---------------\n");
}
