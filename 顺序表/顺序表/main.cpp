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
	printf("����0~9����ֵ��\n");
	show(&ps);
	printf("------------------\n");
	int pos = Search(&ps, 6);
	printf("����6��λ��Ϊ��%d\n", pos);
	printf("------------------\n");
	DeletePos(&ps, pos);
	printf("���ݲ��ҵ�6��λ��ɾ����Ԫ��:\n");
	show(&ps);
	printf("------------------\n");
	DeleteVal(&ps, 3);
	printf("ɾ��Ԫ��3��\n");
	show(&ps);
	printf("------------------\n");
	Destroy(&ps);
	printf("����\n");
	Destroy(&ps);
	show(&ps);
	return 0;
}