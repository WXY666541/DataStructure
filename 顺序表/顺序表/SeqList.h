#pragma once
#define SIZE 20
typedef struct SeqList
{
	int* elem;
	int size;
	int length;
}SeqList, * SqList;

void InitSeq(SqList ps);
bool InsertSeq(SqList ps, int pos, int val);
int  Search(SqList ps, int key);
bool DeletePos(SqList ps, int pos);
bool DeleteVal(SqList ps, int key);
void Destroy(SqList ps);
void show(SqList ps);