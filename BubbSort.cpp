#include<iostream>


void BubbleSort(int* arr, int n)
{
	int temp;//用于交换顺序

	//外层循环，控制趟数
	for (int i = 0; i < n - 1; i++)
	{
		//内存循环，选出最大的数字排到最后面
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
	std::cout << "排序前的数组：";
	show(arrrr, n);
	BubbleSort(arrrr, n);
	std::cout << "排序后的数组：";
	show(arrrr, n);
}


