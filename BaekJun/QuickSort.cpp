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
	int i = pivot + 1; // 왼쪽 시작 지점
	int j = end; // 오른쪽 시작 지점
	int temp;

	cout << "pivot: " << arr[pivot] << "\n\n";
	cout << "Before: ";
	PrintList();

	// i와 j가 엇갈릴때까지 반복
	while (i <= j)
	{
		while (i <= end && arr[i] <= arr[pivot])
			i++;

		while (j > start && arr[j] >= arr[pivot])
			j--;

		if (i > j) // i와 j가 엇갈린 경우
		{
			temp = arr[j];
			arr[j] = arr[pivot];
			arr[pivot] = temp;
		}
		else // i번째 값과 j번째 값을 Swap
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
	
	cout << "정렬 전: ";
	PrintList();
	cout << "\n\n";

	Quick_Sort(0, n - 1);

	cout << "\n\n정렬 후: ";
	PrintList();

	return 0;
}