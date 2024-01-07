#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> nums;
bool used[1001];

void dfs(int idx)
{
	if (idx == m)
	{
		for (auto& num : nums)
		{
			cout << num << " ";
		}
		cout << '\n';
		return;
	}

	for (int i = 1; i <= n; i++)
	{
		if (!used[i])
		{
			used[i] = true;
			nums.push_back(i);
			dfs(idx + 1);
			nums.pop_back();
			used[i] = false;
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;

	dfs(0);

	return 0;
}