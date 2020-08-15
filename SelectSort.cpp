#include<iostream>

#if 0
void SelectSort(int* arr, int n)
{
	int minindex ;
	int temp;
	int i, j;
	for (i = 0; i < n - 1; i++)
	{
		minindex = i;
		for (j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[minindex])
			{
				minindex = j;
			}
		}
		if (i != minindex)
		{
			temp = arr[i];
			arr[i] = arr[minindex];
			arr[minindex] = temp;
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
	SelectSort(arrrr, n);
	std::cout << "排序后的数组：";
	show(arrrr, n);
}
#endif

