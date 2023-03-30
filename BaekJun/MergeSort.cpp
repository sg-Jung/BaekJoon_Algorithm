#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>

#define N 10000

using namespace std;

vector<int> arr = vector<int>(N);
vector<int> result = vector<int>(N);

void merges(int left, int right)
{
	int mid = (left + right) / 2;
	int i = left;
	int j = mid + 1;
	int k = left;

	while (i <= mid && j <= right)
	{
		if (arr[i] < arr[j])
		{
			result[k++] = arr[i++];
		}
		// 양쪽 리스트에서 최솟값을 비교했는데 오른쪽 리스트가 더 컸을 경우
		// 그대로 왼쪽 리스트의 최솟값이 결과배열에 내려오면 된다.
		else
		{
			result[k++] = arr[j++];
		}
	}

	// 오른쪽 리스트에 아직 결과배열에 들어가지 못한 값이 있으면 그대로 넣어준다.
	if (i <= mid)
	{
		while (i <= mid)
		{
			result[k++] = arr[i++];
		}
	}
	else // 남은 값들을 차례로 마저 넣어주는 과정
	{
		while (j <= right)
		{
			result[k++] = arr[j++];
		}
	}

	// 다시 원래 배열에 옮겨담는 과정
	for (int i = left; i <= right; i++)
	{
		arr[i] = result[i];
	}
}

void partition(int left, int right)
{
	int mid;

	// 두개로 분할하고, 병합하는 과정
	// 병합 함수 merges를 보면 알 수 있듯이, while문 둥으로 정렬하면서 병합한다.
	if (left < right)
	{
		mid = (left + right) / 2;
		partition(left, mid);
		partition(mid + 1, right);
		merges(left, right);
	}
}

int main()
{
	arr = { 3, 5, 4, 2, 1, 8, 7, 10, 9, 15, 12, 11, 13, 14};

	int n = arr.size();
	
	partition(0, n - 1);

	// 정렬된 값 출력
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
	return 0;
}