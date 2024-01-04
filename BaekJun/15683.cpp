#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int n, m, ans = 2147483647;
vector<vector<int>> room(8, vector<int>(8));
vector<pair<int, int>> cctv;
int dx[] = { 0, -1, 0, 1 };
int dy[] = { 1, 0, -1, 0 };

void check(int x, int y, int dir)
{
	dir %= 4;

	while (1)
	{
		int nx = x + dx[dir];
		int ny = y + dy[dir];

		x = nx;
		y = ny;

		if (nx < 0 || ny < 0 || nx >= n || ny >= m) return;
		if (room[nx][ny] == 6) return;
		if (room[nx][ny] != 0) continue;

		room[nx][ny] = -1;
	}
}

void dfs(int idx)
{
	if (idx == cctv.size())
	{
		int count = 0;
		for(int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (room[i][j] == 0) count++;

		ans = min(ans, count);

		return;
	}

	int x = cctv[idx].first;
	int y = cctv[idx].second;
	int temp[8][8];

	for (int dir = 0; dir < 4; dir++)
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				temp[i][j] = room[i][j];

		if (room[x][y] == 1)
		{
			check(x, y, dir);
		}
		else if (room[x][y] == 2)
		{
			check(x, y, dir);
			check(x, y, dir + 2);
		}
		else if (room[x][y] == 3)
		{
			check(x, y, dir);
			check(x, y, dir + 1);
		}
		else if (room[x][y] == 4)
		{
			check(x, y, dir);
			check(x, y, dir + 1);
			check(x, y, dir + 2);

		}
		else if (room[x][y] == 5)
		{
			check(x, y, dir);
			check(x, y, dir + 1);
			check(x, y, dir + 2);
			check(x, y, dir + 3);
		}

		dfs(idx + 1);

		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				room[i][j] = temp[i][j];

		cout << idx << endl;
	}
}

int main()
{
	cin >> n >> m;
	for(int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			cin >> room[i][j];
			if (room[i][j] >= 1 && room[i][j] <= 5) cctv.push_back(make_pair(i, j));
		}
	dfs(0);

	cout << ans << '\n';

	return 0;
}