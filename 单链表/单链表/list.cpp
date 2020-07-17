#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"list.h"

//³õÊ¼»¯
void InitList(List plist)
{
	assert(plist != NULL);
	if (plist == NULL)
	{
		return;
	}
	plist->next = NULL;
}
//Í·²å
bool Insert_Head(List plist, int val)
{
	assert(plist != NULL);
	if (plist == NULL)
	{
		return false;
	}

	Node* p = (Node*)malloc(sizeof(Node));
	p->data = val;

	p->next = plist->next;
	plist->next = p;

	return true;
}
//Î²²å
bool Insert_Tail(List plist, int val)
{
	assert(plist != NULL);
	if (plist == NULL)
	{
		return false;
	}

	Node* p = (Node*)malloc(sizeof(Node));
	p->data = val;

	Node* q;
	for (q = plist; q->next != NULL; q = q->next);
	q->next = p;
	p->next = NULL;
	return true;	
}
//É¾³ý¹Ø¼ü×Ö
bool Delete(List plist, int key)
{
	assert(plist != NULL);
	if (plist == NULL)
	{
		return false;
	}

	Node* p;
	Node* q;
	for (p = plist; p->next != NULL; p = p->next)
	{
		if (p->next->data == key)
		{
			q = p->next;
			p->next = q->next;
			free(q);
			return true;
		}
	}
	return false;
}
//´òÓ¡
void show(List plist)
{
	Node* p = plist->next;
	for (p; p != NULL; p = p->next)
	{
		printf("%d ", p->data);
	}
	printf("\n");
}

//Ïú»Ù
void Destroy(List plist)
{
	Node* p;
	while (plist->next != NULL)
	{
		p = plist->next;
		plist->next = p->next;
		free(p);
	}
}
//ÄæÖÃ
void Reverse(List plist)
{
	if (plist == NULL || plist->next == NULL ||
		plist->next->next == NULL)
		return;


	Node* p = plist->next;
	plist->next = NULL;

	Node* q;
	while (p != NULL)
	{
		q = p->next;
		p->next = plist->next;
		plist->next = p;

		p = q;
	}
}