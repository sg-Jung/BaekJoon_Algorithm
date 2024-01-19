#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int n, k;
queue<pair<int, int>> q; // { 누나, 시간 }
bool visited[500001][2];

void bfs()
{
	q.push({ n,  0 });
	visited[n][0] = true;

	while (!q.empty())
	{
		int x = q.front().first;
		int time = q.front().second;
		int y = k + time * (time + 1) / 2; //  {k + (1 + 2 + 3 ...)}
		q.pop();

		printf("x: %d, y: %d, time: %d\n", x, y, time);

		if (visited[y][time % 2])
		{
			cout << time << '\n';
			return;
		}

		if (y < 0 || y > 500000)
		{
			cout << "-1" << '\n';
			return;
		}

		++time;

		for (int num : {x - 1, x + 1, x * 2})
		{
			if (num < 0 or num > 500000) continue;
			if (visited[num][time % 2]) continue;

			visited[num][time % 2] = true;
			q.push({ num, time });
		}
	}
}

int main()
{
	cin >> n >> k;
	bfs();

	return 0;
}