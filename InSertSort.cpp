#include<iostream>
#include<vector>

#if 0
void SelectSort(int arr[],int n)
{
	//���ȶ�����������
	int i, j, temp;

	//��������δ��������
	for (i = 1; i < n; i++)
	{
		int temp = arr[i];//���浱ǰҪ�������ֵ

		//��������������в��Ҹ�Ԫ�ز����λ��
		for (j = i - 1; j >= 0; j--)
		{
			//������������Ԫ��һֱ����temp���Ͱ�Ԫ���������
			if (arr[j] > temp)
			{
				arr[j + 1] = arr[j];//ע��㣡�������arr[j] = arr[j-1]���ܻ����Խ������
			}
			else//�ҵ��˲���λ��
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
	std::cout << "����ǰ�����飺";
	show(arrrr, n);
	SelectSort1(arrrr, n);
	std::cout << "���������飺";
	show(arrrr, n);	
}
#endif