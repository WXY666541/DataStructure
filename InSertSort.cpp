#include<iostream>
#include<vector>

#if 0
void SelectSort(int arr[],int n)
{
	//首先定义三个变量
	int i, j, temp;

	//挨个遍历未排序序列
	for (i = 1; i < n; i++)
	{
		int temp = arr[i];//保存当前要排序的数值

		//在已排序的序列中查找该元素插入的位置
		for (j = i - 1; j >= 0; j--)
		{
			//不满足条件，元素一直大于temp，就把元素整体后移
			if (arr[j] > temp)
			{
				arr[j + 1] = arr[j];//注意点！！如果用arr[j] = arr[j-1]可能会出现越界的情况
			}
			else//找到了插入位置
			{
				break;
			}
		}
		arr[j + 1] = temp;
	}
}


void SelectSort1(int arr[], int n)
{
	int i, j, temp;
	for (i = 1; i < n; i++)
	{
		temp = arr[i];
		for (j = i - 1; j >= 0; j--)
		{
			if (arr[j] > temp)
			{
				arr[j + 1] = arr[j];
			}
			else
			{
				break;
			}
		}
		arr[j + 1] = temp;
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
	int arrrr[] = { 0,5,2,6,1,3 };
	int n = sizeof(arrrr) / sizeof(arrrr[0]);
	std::cout << "排序前的数组：";
	show(arrrr, n);
	SelectSort1(arrrr, n);
	std::cout << "排序后的数组：";
	show(arrrr, n);	
}
#endif