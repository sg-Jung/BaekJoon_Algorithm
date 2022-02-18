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

	int last = 1000 - n;
	int count = 0;

	int money[6] = { 500, 100, 50, 10, 5, 1 };

	for (int i = 0; i < 6; i++)
	{
		count += last / money[i];
		last = last % money[i];
	}

	cout << count;

	return 0;
}