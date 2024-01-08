#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int n, m, ans = 0;
bool nomix[201][201];
bool used[1001];

void Combination(vector<int>& ary, int r, int index)
{
	if (r == ary.size())
	{
		for (int i = 0; i < ary.size() - 1; i++)
			for (int j = i + 1; j < ary.size(); j++)
				if (nomix[ary[i]][ary[j]]) return;
		
		ans++;
		return;
	}

	for (int i = index; i <= n; i++)
	{
		if (!used[i])
		{
			used[i] = true;
			ary.push_back(i);
			Combination(ary, r, i);
			ary.pop_back();
			used[i] = false;
		}
	}
}

int main()
{
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		nomix[a][b] = nomix[b][a] = true;
	}
	
	vector<int> ary;
	Combination(ary, 3, 1);

	cout << ans << endl;

	return 0;
}