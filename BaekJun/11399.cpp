#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
	int N, temp;
	int sum = 0;
	cin >> N;

	vector<int> time = vector<int>();

	for (int i = 0; i < N; i++)
	{
		cin >> temp;
		time.push_back(temp);
	}

	sort(time.begin(), time.end());

	temp = 0;

	for (int i = 0; i < time.size(); i++)
	{
		for (int j = 0; j < i + 1; j++)
		{
			temp += time[j];
		}

		sum += temp;
		temp = 0;
	}
	cout << sum;
}