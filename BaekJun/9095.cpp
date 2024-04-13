#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int t;
vector<int> a(1001);
vector<int> ans(1001, 0);

void dfs(int sum, int res, int idx)
{	
	if (sum > res) return;
	if (sum == res)
	{
		ans[idx]++;
		return;
	}

	dfs(sum + 1, res, idx);
	dfs(sum + 2, res, idx);
	dfs(sum + 3, res, idx);
}

int main()
{
	cin >> t;

	for (int i = 0; i < t; i++)
		cin >> a[i];
	
	for (int i = 0; i < t; i++)
	{
		dfs(1, a[i], i);
		dfs(2, a[i], i);
		dfs(3, a[i], i);
	}

	for (int i = 0; i < t; i++)
		cout << ans[i] << endl;

	return 0;
}