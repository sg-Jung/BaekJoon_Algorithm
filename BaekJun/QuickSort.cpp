#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>

#define N 10000

using namespace std;

vector<int> arr = vector<int>(N);

void PrintList()
{
	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr[i] << " ";
	}

	cout << "\n\n";
}

void Quick_Sort(int start, int end)
{
	if (start >= end) return;

	int pivot = start;
	int i = pivot + 1; // ���� ���� ����
	int j = end; // ������ ���� ����
	int temp;

	cout << "pivot: " << arr[pivot] << "\n\n";
	cout << "Before: ";
	PrintList();

	// i�� j�� ������������ �ݺ�
	while (i <= j)
	{
		while (i <= end && arr[i] <= arr[pivot])
			i++;

		while (j > start && arr[j] >= arr[pivot])
			j--;

		if (i > j) // i�� j�� ������ ���
		{
			temp = arr[j];
			arr[j] = arr[pivot];
			arr[pivot] = temp;
		}
		else // i��° ���� j��° ���� Swap
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	cout << "After: ";
	PrintList();

	Quick_Sort(start, j - 1);
	Quick_Sort(j + 1, end);
}

int main()
{
	//arr = { 3, 5, 4, 2, 1, 8, 7, 10, 9, 15, 12, 6, 11, 13, 14};
	arr = { 7, 1, 3, 5, 9, 2, 8, 4, 6 };

	int n = arr.size();
	
	cout << "���� ��: ";
	PrintList();
	cout << "\n\n";

	Quick_Sort(0, n - 1);

	cout << "\n\n���� ��: ";
	PrintList();

	return 0;
}