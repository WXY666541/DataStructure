#include<iostream>
using namespace std;
#if 0
int Partition(int* arr, int low, int high)
{
	int temp = arr[low];
	while (low < high)
	{
		while (low < high && arr[high] >= temp)
		{
			high--;
		}
		arr[low] = arr[high];
		while (low < high && arr[low] <= temp)
		{
			low++;
		}
		arr[high] = arr[low];
	}
	arr[low] = temp;
	return low;
}

void Quick(int* arr, int low, int high)
{
	int pivot = Partition(arr, low, high);
	if (low < pivot)
	{
		Quick(arr, low, pivot - 1);
	}
	if (pivot < high)
	{
		Quick(arr, pivot +1,high);
	}
}

void QuickSort(int* arr, int n)
{
	Quick(arr, 0, n - 1);
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
	int arrrr[] = { 10,6,7,1,3,9,4,2 };
	int n = sizeof(arrrr) / sizeof(arrrr[0]);
	std::cout << "排序前的数组：";
	show(arrrr, n);
	QuickSort(arrrr, n);
	std::cout << "排序后的数组：";
	show(arrrr, n);
}
#endif
