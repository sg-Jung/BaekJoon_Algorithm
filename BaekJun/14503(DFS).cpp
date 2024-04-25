#include <iostream>

using namespace std;

int n, m, ans;
int map[51][51];
bool visited[51][51];

// ºÏ µ¿ ³² ¼­ 0 1 2 3
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

bool checkInRange(int y, int x)
{
	if (y < 0 || y > n - 1 || x < 0 || x > m - 1)
		return false;
	if (map[y][x] == 1)
		return false;

	return true;
}

void dfs(pair<int, int> robot, int d, int ans)
{
	for (int i = 0; i < 4; i++)
	{
		int nDir = (d + 3 - i) % 4;
		int ny = robot.first + dy[nDir];
		int nx = robot.second + dx[nDir];

		if (checkInRange(ny, nx) && map[ny][nx] == 0 && !visited[ny][nx])
		{
			visited[ny][nx] = true;
			dfs(make_pair(ny, nx), nDir, ans + 1);
		}
	}

	int backD = (d + 2) % 4;

	int by = robot.first + dy[backD];
	int bx = robot.second + dx[backD];

	if (checkInRange(by, bx))
	{
		dfs(make_pair(by, bx), d, ans);
	}
	else
	{
		cout << ans << endl;
		exit(0);
	}
}

int main()
{
	cin >> n >> m;

	pair<int, int> robot;
	int dir;

	cin >> robot.first >> robot.second >> dir;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> map[i][j];
		}
	}
	
	visited[robot.first][robot.second] = true;
	ans++;
	dfs(robot, dir, ans);

	return 0;
}