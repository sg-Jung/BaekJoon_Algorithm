#include <iostream>
#include <vector>

using namespace std;

int n, m, ans = 2147483647;
int map[51][51];
bool used[1001];
vector<pair<int, int>> house, chicken, choose;

void Combination(vector<pair<int, int>>& chicken, vector<pair<int, int>>& choose, int r, int index)
{
	if (r == choose.size())
	{
		int sum = 0;
		for (int i = 0; i < house.size(); i++)
		{
			int temp = 2147483647;
			for (int j = 0; j < choose.size(); j++)
			{
				int cal = abs(house[i].first - choose[j].first) + abs(house[i].second - choose[j].second);
				temp = min(temp, cal);
			}
			sum += temp;
		}
		ans = min(ans, sum);
		return;
	}

	for (int i = index; i < chicken.size(); i++)
	{
		if (!used[i])
		{
			used[i] = true;
			choose.push_back(chicken[i]);
			Combination(chicken, choose, r, i);
			choose.pop_back();
			used[i] = false;
		}
	}
}

int main()
{
	cin >> n >> m;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 1)
				house.push_back({ i, j });
			else if (map[i][j] == 2)
				chicken.push_back({ i, j });
		}

	Combination(chicken, choose, m, 0);

	cout << ans << '\n';

	return 0;
}
