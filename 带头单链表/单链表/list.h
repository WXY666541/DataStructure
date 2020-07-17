#pragma once
typedef struct Node
{
	int data;
	struct Node* next;

}Node,*List;

//³õÊ¼»¯
void InitList(List plist);
//Í·²å
bool Insert_Head(List plist, int val);
//Î²²å
bool Insert_Tail(List plist, int val);
//É¾³ı¹Ø¼ü×Ö
bool Delete(List plist, int key);
//´òÓ¡
void show(List plist);
//Ïú»Ù
void Destroy(List plist);
//ÄæÖÃ
void Reverse(List plist);
