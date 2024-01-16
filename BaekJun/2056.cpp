#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int n;
int times[10001], inDegree[10001], dp[10001];
vector<vector<int>> a(10001);
queue<int> q;

int main()
{
	cin >> n;

	for (int i = 1; i <= n; i++)
	{
		int t, l;
		cin >> t >> l;
		times[i] = t;
		dp[i] = t;
		for (int j = 0; j < l; j++)
		{
			int x;
			cin >> x;
			a[x].push_back(i);
			inDegree[i]++;
		}
	}

	for (int i = 1; i <= n; i++)
		if (inDegree[i] == 0) q.push(i);

	while (!q.empty())
	{
		int x = q.front();
		q.pop();

		for (int i = 0; i < a[x].size(); i++)
		{
			int y = a[x][i];
			inDegree[y]--;
			dp[y] = max(dp[y], dp[x] + times[y]);
			if (inDegree[y] == 0)
				q.push(y);
		}
	}

	int result = -1;

	for (int i = 1; i <= n; i++)
		result = max(result, dp[i]);

	cout << result << '\n';
	return 0;
}