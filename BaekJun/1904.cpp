#include <iostream>

using namespace std;

int n;
long long dp[1000001];

int main()
{
	cin >> n;
	dp[1] = 1;
	dp[2] = 2;

	if (n < 3)
	{
		cout << dp[n] << '\n';
		return 0;
	}

	for (int i = 3; i <= n; i++)
	{
		dp[i] = (dp[i - 1] + dp[i - 2]) % 15746;
	}

	cout << dp[n] << '\n';


	return 0;
}