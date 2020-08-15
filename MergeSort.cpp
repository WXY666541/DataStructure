#include<iostream>
#include<malloc.h>
using namespace std;

//һ�˹鲢�Ĺ���
void Merge(int* arr, int n, int gap)
{
	int low1 = 0;//��һ���鲢�ε���ʼλ��
	int high1 = low1 + gap - 1;//��һ���鲢�ε�ĩβλ��
	int low2 = high1 + 1;//�ڶ����鲢�ε���ʼλ��
	int high2 = low2 + gap  > n ? n - 1 : low2 + gap - 1;//�ڶ����鲢�ε�ĩβλ��

	//�¿���һ�������Ź鲢���˵�����
	int* brr = (int*)malloc(n * sizeof(int));
	int i = 0;//�������¿����������ʼ�±�

	//�������������鲢�ε����
	while (low2 < n)
	{
		//�����鲢�ζ���������
		while (low1 <= high1 && low2 <= high2)
		{
			if (arr[low1] <= arr[low2])
			{
				brr[i++] = arr[low1++];
			}
			else
			{
				brr[i++] = arr[low2++];
			}
		}


		//ֻ��һ���鲢�ε����
		while (low1 <= high1)
		{
			brr[i++] = arr[low1++];
		}
		while (low2 <= high2)
		{
			brr[i++] = arr[low2++];
		}

		//�¸��鲢�μ���
		low1 = high2 + 1;
		high1 = low1 + gap - 1;
		low2 = high1 + 1;
		high2 = low2 + gap > n ? n - 1 : low2 + gap - 1;
	}

	//ֻ��һ���鲢������
	while (low1 < n)
	{
		brr[i++] = arr[low1++];
	}

	//������е����ݴ�brr�����¿�����arr����
	for (int i = 0; i < n; i++)
	{
		arr[i] = brr[i];
	}
	free(brr);
}

void MergeSort(int* arr, int n)
{
	for (int i = 1; i < n; i *= 2)
	{
		Merge(arr, n, i);
	}
}
void show(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}
int main()
{
	int arrrr[] = {10,6,7,1,3,9,4,2 };
	int n = sizeof(arrrr) / sizeof(arrrr[0]);
	std::cout << "����ǰ�����飺";
	show(arrrr, n);
	MergeSort(arrrr, n);
	std::cout << "���������飺";
	show(arrrr, n);
}