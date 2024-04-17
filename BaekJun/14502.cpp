#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAX_N 8
#define MAX_M 8

int map[MAX_N][MAX_M], tmp[MAX_N][MAX_M];
bool visit[MAX_N][MAX_M], virus_visit[MAX_N][MAX_M];
int N, M, ans = 0;
int dy[4] = {1, 0 , -1, 0};
int dx[4] = {0, 1, 0, -1};
vector<pair<int, int>> wall;

// 바이러스를 퍼뜨리기 위한 bfs
void bfs()
{
	queue<pair<int, int>> q;
	memset(virus_visit, false, sizeof(virus_visit));

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			tmp[i][j] = map[i][j];

			if (2 == tmp[i][j])
			{
				q.push(make_pair(i, j));
				virus_visit[i][j] = true;
			}
		}
	}

	for (int i = 0; i < wall.size(); i++)
	{
		pair<int, int> pos = wall[i];
		tmp[pos.first][pos.second] = 1;
	}

	while (!q.empty())
	{
		pair<int, int> virus = q.front();
		q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			int ny = virus.first + dy[dir];
			int nx = virus.second + dx[dir];

			if (ny < 0 || ny >= N || nx < 0 || nx >= M) 
				continue;

			if (tmp[ny][nx] == 0 && !virus_visit[ny][nx])
			{
				virus_visit[ny][nx] = true;
				tmp[ny][nx] = 2;

				q.push(make_pair(ny, nx));
			}
		}
	}
}


// 벽을 3군데 세우기 위한 조합 dfs (2차원 배열로 조합 구현)
void dfs(int row, int col)
{
	if (3 == wall.size())
	{
		bfs();
		ans = max(ans, countSetPlace());

		return;
	}

	for (int i = row; i < N; i++)
	{
		// 행 i가 row와 같다면, 열이 row보다 작은 col은 이미 이전에 확인을 다 했기 때문에 col열부터 확인하도록 해야함
		// 행 i가 row와 같지 않다면, 0번 열부터 확인
		int col2 = (i == row) ? col : 0;

		for (int j = col2; j < M; j++)
		{
			if (!visit[i][j] && map[i][j] == 0)
			{
				visit[i][j] = true;
				wall.push_back(make_pair(i, j));
				dfs(i, j);
				wall.pop_back();
				visit[i][j] = false;
			}
		}
	}
}


int countSetPlace()
{
	int count = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (tmp[i][j] == 0)
				count++;
		}
	}

	return count;
}


int main()
{
	cin >> N >> M;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];
		}
	}

	dfs(0, 0);

	cout << ans << '\n';

	return 0;
}