#include <iostream>
#include <vector>

using namespace std;

int n, m;
int map[8][8];
vector<pair<int, int>> cctv;
int dx[] = { 0, -1, 0, 1 };
int dy[] = { 1, 0, -1, 0 };

int answer = 2147483647;

void check(int x, int y, int dir)
{
	dir %= 4;

	while (1)
	{
		int newX = x + dx[dir];
		int newY = y + dy[dir];

		x = newX;
		y = newY;

		if (newX < 0 || newY < 0 || newX >= n || newY >= m) break;
		if (map[newX][newY] == 6) break;
		if (map[newX][newY] != 0) continue;
		map[newX][newY] = -1;
	}
}

void dfs(int idx)
{
	if (idx == cctv.size())
	{
		int ans = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (map[i][j] == 0) ans++;

		answer = min(answer, ans);
		return;
	}

	int temp[8][8];

	int x = cctv[idx].first;
	int y = cctv[idx].second;

	for (int dir = 0; dir < 4; dir++)
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				temp[i][j] = map[i][j];

		if (map[x][y] == 1)
		{
			check(x, y, dir);
		}
		else if (map[x][y] == 2)
		{
			check(x, y, dir);
			check(x, y, dir + 2);
		}
		else if (map[x][y] == 3)
		{
			check(x, y, dir);
			check(x, y, dir + 1);
		}
		else if (map[x][y] == 4)
		{
			check(x, y, dir);
			check(x, y, dir + 1);
			check(x, y, dir + 2);
		}
		else if (map[x][y] == 5)
		{
			check(x, y, dir);
			check(x, y, dir + 1);
			check(x, y, dir + 2);
			check(x, y, dir + 3);
		}

		dfs(idx + 1);

		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				map[i][j] = temp[i][j];
	}
}

int main()
{
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			cin >> map[i][j];
			if (map[i][j] != 0 && map[i][j] != 6) cctv.push_back({ i, j });
		}

	dfs(0);

	cout << answer << endl;

	return 0;
}