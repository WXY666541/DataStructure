#include<iostream>

#if 0
//每一组组内排序，流程和直接插入排序一样
void Shell(int* arr,int n, int gap)
{
	int i,j, temp;
	for (i = gap; i < n; i++)
	{
		temp = arr[i];
		for (j = i - gap; j >= 0; j -= gap)
		{
			if (arr[j] > temp)
			{
				arr[j + gap] = arr[j];
			}
			else
			{
				break;
			}
		}
		arr[j + gap] = temp;
	}
}

//首先进行分组
void ShellSort(int* arr, int n)
{
	int dp[] = { 5,3,1 };
	for (int i = 0; i < sizeof(dp) / sizeof(dp[0]); i++)
	{
		Shell(arr, n,dp[i]);
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
	int arrrr[] = { 9,1,25,7,4,8,6,3,5 };
	int n = sizeof(arrrr) / sizeof(arrrr[0]);
	std::cout << "排序前的数组：";
	show(arrrr, n);
	ShellSort(arrrr, n);
	std::cout << "排序后的数组：";
	show(arrrr, n);
}
#endif