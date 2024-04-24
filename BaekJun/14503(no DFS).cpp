#include <iostream>

using namespace std;

int n, m, ans;
int map[51][51];
bool visited[51][51];

// ºÏ µ¿ ³² ¼­ 0 1 2 3
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

bool checkInRange(int y, int x)
{
	if (y < 0 || y > n - 1 || x < 0 || x > m - 1)
		return false;
	if (map[y][x] == 1)
		return false;

	return true;
}

bool isExistCleanArea(pair<int, int> robot)
{
	for (int i = 0; i < 4; i++)
	{
		int ny = robot.first + dy[i];
		int nx = robot.second + dx[i];

		if (!checkInRange(ny, nx)) continue;

		if (!visited[ny][nx])
			return true;
	}

	return false;
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

	while (1)
	{
		if (!visited[robot.first][robot.second] && map[robot.first][robot.second] == 0)
		{
			visited[robot.first][robot.second] = true;
			ans++;
		}

		if (isExistCleanArea(robot))
		{
			for (int i = 0; i < 4; i++)
			{
				int nDir = (dir + 3 - i) % 4;
				int ny = robot.first + dy[nDir];
				int nx = robot.second + dx[nDir];

				if (!checkInRange(ny, nx)) continue;

				if (map[ny][nx] == 0 && !visited[ny][nx])
				{
					robot = { ny, nx };
					dir = nDir;
					break;
				}
			}
		}
		else
		{
			int backD = (dir + 2) % 4;

			int by = robot.first + dy[backD];
			int bx = robot.second + dx[backD];

			if (checkInRange(by, bx))
			{
				robot = { by, bx };
			}
			else
			{
				break;
			}
		}
	}

	cout << ans << endl;

	return 0;
}