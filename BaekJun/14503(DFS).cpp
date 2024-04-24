#include <iostream>

using namespace std;

int n, m, ans;
int map[51][51];
bool visited[51][51];

// ºÏ µ¿ ³² ¼­ 0 1 2 3
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

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

	return 0;
}