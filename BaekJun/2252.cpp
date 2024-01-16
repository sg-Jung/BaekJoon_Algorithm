#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m;

int main()
{
	cin >> n >> m;
	
	vector<vector<int>> a(n + 1);
	vector<int> degree(n + 1);

	for (int i = 0; i < m; i++)
	{
		int x, y;
		cin >> x >> y;
		a[x].push_back(y);
		degree[y]++;
	}
	
	queue<int> q;

	for (int i = 1; i <= n; i++)
		if (degree[i] == 0) q.push(i);

	while (!q.empty())
	{
		int x = q.front();
		q.pop();
		printf("%d ", x);

		for (int i = 0; i < a[x].size(); i++)
		{
			int y = a[x][i];
			degree[y]--;
			if (degree[y] == 0) q.push(y);
		}
	}

	return 0;
}