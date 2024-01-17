#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int t, N;
vector<int> dp(1001), ans;

int main()
{
	cin >> t;

	dp[1] = 1;
	dp[2] = 2;
	dp[3] = 4;

	for (int i = 0; i < t; i++)
	{
		cin >> N;

		for (int n = 4; n <= N; n++)
		{
			dp[n] = dp[n - 1] + dp[n - 2] + dp[n - 3];
		}
		ans.push_back(dp[N]);
	}

	for (int i = 0; i < ans.size(); i++) cout << ans[i] << endl;

	return 0;
}