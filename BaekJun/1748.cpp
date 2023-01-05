#include<iostream>

using namespace std;

int main()
{
	int n;
	cin >> n;
	long long ans = 0;

	for (int s = 1, len = 1; s <= n; s *= 10, len++)
	{
		int e = s * 10 - 1;
		if (e > n) e = n;

		ans += (long long)(e - s + 1) * len;
	}

	cout << ans << '\n';
	return 0;
}