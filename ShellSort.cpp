#include<iostream>

#if 0
//ÿһ�������������̺�ֱ�Ӳ�������һ��
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

//���Ƚ��з���
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
	std::cout << "����ǰ�����飺";
	show(arrrr, n);
	ShellSort(arrrr, n);
	std::cout << "���������飺";
	show(arrrr, n);
}
#endif