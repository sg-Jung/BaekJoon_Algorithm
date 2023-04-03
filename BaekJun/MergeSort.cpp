#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>

#define N 10000

using namespace std;

vector<int> arr = vector<int>(N);
vector<int> result = vector<int>(N);

void PrintList()
{
	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr[i] << " ";
	}

	cout << "\n\n";
}

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
		// ���� ����Ʈ���� �ּڰ��� ���ߴµ� ������ ����Ʈ�� �� ���� ���
		// �״�� ���� ����Ʈ�� �ּڰ��� ����迭�� �������� �ȴ�.
		else
		{
			result[k++] = arr[j++];
		}
	}

	// ������ ����Ʈ�� ���� ����迭�� ���� ���� ���� ������ �״�� �־��ش�.
	if (i <= mid)
	{
		while (i <= mid)
		{
			result[k++] = arr[i++];
		}
	}
	else // ���� ������ ���ʷ� ���� �־��ִ� ����
	{
		while (j <= right)
		{
			result[k++] = arr[j++];
		}
	}

	// �ٽ� ���� �迭�� �Űܴ�� ����
	for (int i = left; i <= right; i++)
	{
		arr[i] = result[i];
	}

	cout << "merges(left: " << left << ", right: " << right << "): ";
	PrintList();
}

void partition(int left, int right)
{
	int mid;

	// �ΰ��� �����ϰ�, �����ϴ� ����
	// ���� �Լ� merges�� ���� �� �� �ֵ���, while�� ������ �����ϸ鼭 �����Ѵ�.
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
	// arr = { 3, 5, 4, 2, 1, 8, 7, 10, 9, 15, 12, 6, 11, 13, 14};
	arr = { 7, 1, 3, 5, 9, 2, 8, 4, 6 };

	int n = arr.size();

	cout << "���� ��: ";
	PrintList();
	cout << "\n\n";
	
	partition(0, n - 1);

	// ���ĵ� �� ���
	cout << "\n\n���� ��: ";
	PrintList();

	return 0;
}