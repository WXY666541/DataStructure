#include<iostream>
#include<malloc.h>
using namespace std;

//一趟归并的过程
void Merge(int* arr, int n, int gap)
{
	int low1 = 0;//第一个归并段的起始位置
	int high1 = low1 + gap - 1;//第一个归并段的末尾位置
	int low2 = high1 + 1;//第二个归并段的起始位置
	int high2 = low2 + gap  > n ? n - 1 : low2 + gap - 1;//第二个归并段的末尾位置

	//新开辟一个数组存放归并好了的数据
	int* brr = (int*)malloc(n * sizeof(int));
	int i = 0;//并定义新开辟数组的起始下标

	//总体上有两个归并段的情况
	while (low2 < n)
	{
		//两个归并段都还有数据
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


		//只有一个归并段的情况
		while (low1 <= high1)
		{
			brr[i++] = arr[low1++];
		}
		while (low2 <= high2)
		{
			brr[i++] = arr[low2++];
		}

		//下个归并段继续
		low1 = high2 + 1;
		high1 = low1 + gap - 1;
		low2 = high1 + 1;
		high2 = low2 + gap > n ? n - 1 : low2 + gap - 1;
	}

	//只有一个归并段留下
	while (low1 < n)
	{
		brr[i++] = arr[low1++];
	}

	//最后将所有的数据从brr中重新拷贝回arr当中
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
	std::cout << "排序前的数组：";
	show(arrrr, n);
	MergeSort(arrrr, n);
	std::cout << "排序后的数组：";
	show(arrrr, n);
}