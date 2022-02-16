#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
	int n, k, temp;
	cin >> n >> k;

	vector<int> coin = vector<int>();

	for (int i = 0; i < n; i++)
	{
		cin >> temp;
		coin.push_back(temp);
	}

	reverse(coin.begin(), coin.end());

	int min = 0;

	for (int i = 0; i < n; i++)
	{
		if (k / coin[i] == 0)
			continue;

		min += k / coin[i];

		k = k % coin[i];
	}

	cout << min;

	return 0;
}