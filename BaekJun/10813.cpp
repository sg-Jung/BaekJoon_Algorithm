#include <iostream>

using namespace std;

int n, m;
int arr[101];

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

int main()
{
	cin >> n >> m;

	for (int i = 1; i <= n; i++)
	{
		arr[i] = i;
	}

	for (int k = 0; k < m; k++)
	{
		int i, j;
		cin >> i >> j;
		swap(arr[i], arr[j]);
	}

	for (int i = 1; i <= n; i++)
	{
		cout << arr[i] << " ";
	}


	return 0;
}