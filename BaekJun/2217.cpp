#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
	int n;
	cin >> n;

	vector<int> kg = vector<int>(n);

	for (int i = 0; i < n; i++)
	{
		cin >> kg[i];
	}

	sort(kg.begin(), kg.end(), greater<int>());

	int max = kg[0] * 1;

	for (int i = 1; i < kg.size(); i++)
	{
		if (kg[i] * (i + 1) > max)
			max = kg[i] * (i + 1);
	}

	cout << max;

	return 0;
}