#pragma once
typedef struct Node
{
	int data;
	struct Node* next;

}Node,*List;

//��ʼ��
void InitList(List plist);
//ͷ��
bool Insert_Head(List plist, int val);
//β��
bool Insert_Tail(List plist, int val);
//ɾ���ؼ���
bool Delete(List plist, int key);
//��ӡ
void show(List plist);
//����
void Destroy(List plist);
//����
void Reverse(List plist);
