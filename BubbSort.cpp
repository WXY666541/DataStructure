#include<iostream>


void BubbleSort(int* arr, int n)
{
	int temp;//���ڽ���˳��

	//���ѭ������������
	for (int i = 0; i < n - 1; i++)
	{
		//�ڴ�ѭ����ѡ�����������ŵ������
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (arr[j] > arr[j +1])
			{
				temp = arr[j];
				arr[j] = arr[j +1];
				arr[j + 1] = temp;
			}
		}
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
	int arrrr[] = { 7,4,5,9,8,2,1 };
	int n = sizeof(arrrr) / sizeof(arrrr[0]);
	std::cout << "����ǰ�����飺";
	show(arrrr, n);
	BubbleSort(arrrr, n);
	std::cout << "���������飺";
	show(arrrr, n);
}


