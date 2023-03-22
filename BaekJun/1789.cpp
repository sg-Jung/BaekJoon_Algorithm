#define _CRT_SECURE_NO_WARNINGS
#include<iostream>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	long long s;
	cin >> s;

	long long n = 1, sum;
	
	while (1)
	{
		sum = (n * (n + 1)) / 2;
		if (sum > s)
		{
			n -= 1;
			break;
		}
		n++;
	}

	cout << n << '\n';

	return 0;
}