#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"SeqList.h"



//��ʼ������
void InitSeq(SqList ps)
{
	//�п�
	assert(ps != NULL);
	if (ps == NULL)
	{
		return;
	}
	//����length��С�ĸ���
	ps->elem = (int*)malloc(sizeof(int) * SIZE);
	ps->size = 0;
	ps->length = SIZE;
}

//����
static bool IsFull(SqList ps)
{
	return ps->length == ps->size;
}

//����
static void Resize(SqList ps)
{
	ps->elem = (int*)realloc(ps->elem, sizeof(int) * ps->size * 2);
	ps->length *= 2;
}
//ָ��λ�ò�������
bool InsertSeq(SqList ps, int pos, int val)
{
	//�п�
	assert(ps != NULL);
	if (ps == NULL)
	{
		return false;
	}

	//�жϲ���λ���Ƿ�Ϸ�
	if (pos < 0 || pos > ps->size)
	{
		return false;
	}

	//�������������Ҫ����
	if (IsFull(ps))
	{
		Resize(ps);
	}

	//���Ʋ���
	for (int i = ps->size - 1; i >= pos; i--)
	{
		ps->elem[i + 1] = ps->elem[i];
	}
	//������ЧԪ�ظ���
	ps->elem[pos] = val;
	ps->size ++ ;
	return true;
}

//��Ԫ�ز����±�
int Search(SqList ps, int key)
{
	//�п�
	assert(ps != NULL);
	if (ps == NULL)
		return -1;

	//ѭ��˳�����
	for (int i = 0; i < ps->size; i++)
	{
		if (ps->elem[i] == key)
		{
			return i;
		}
	}
	return -1;
}

//ɾ��posλ�õ�ֵ
bool DeletePos(SqList ps, int pos)
{
	//�п�
	assert(ps != NULL);
	if (ps == NULL)
	{
		return false;
	}

	//�ж�posλ���Ƿ�Ϸ�
	if (pos < 0 || pos > ps->size)
	{
		return false;
	}

	//ѭ��������ǰ��ɾ��
	for (int i = pos; i < ps->size - 1; i++)
	{
		ps->elem[i] = ps->elem[i + 1];
	}

	//����size�Ĵ�С
	ps->size -= 1;
	return true;
}

//ɾ��key
bool DeleteVal(SqList ps, int key)
{
	//�п�
	assert(ps != NULL);
	if (ps == NULL)
	{
		return false;
	}

	//����Ԫ�أ�����Ҫɾ��Ԫ�ص��±�
	int pos = Search(ps, key);
	//ɾ��
	return DeletePos(ps, pos);
}

//����
void Destroy(SqList ps)
{
	//�п�
	assert(ps != NULL);
	//�ڴ��ͷ�
	free(ps->elem);
	//������Ա���³�ʼ��
	ps->elem = NULL;
	ps->size = 0;
	ps->length = 0;
}

//��ӡ����
void show(SqList ps)
{
	for (int i = 0; i < ps->size; i++)
	{
		printf("%d", ps->elem[i]);
	}
	printf("\n");
}

