#include <iostream>

using namespace std;

int n, m, ans = 100000;

char map[11][11];
bool visit[11][11][11][11];
int mry, mrx, mby, mbx;

// 좌, 하, 우, 상
int dy[4] = {0, 1, 0, -1};
int dx[4] = {-1, 0, 1, 0};

void move(int& ny, int& nx, int& dist, int dir)
{
	while (map[ny + dy[dir]][nx + dx[dir]] != '#')
	{
		ny += dy[dir];
		nx += dx[dir];
		dist++;

		if (map[ny][nx] == 'O') break;
	}
}


void dfs(int ry, int rx, int by, int bx, int count)
{
	if (count > 10) return;

	if (map[by][bx] == 'O') return; // 파란공이 O에 위치했다면 함수종료
	if (map[ry][rx] == 'O') // 빨간공이 O에 위치했다면 ans 계산
	{
		ans = min(ans, count);
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		int nry = ry, nrx = rx, nby = by, nbx = bx, rd = 0, bd = 0;

		move(nry, nrx, rd, i); // 빨간공 # or O 만날때 까지 이동 & 이동거리 rd로 체크
		move(nby, nbx, bd, i); // 파란공 # or O 만날때 까지 이동 & 이동거리 bd로 체크

		// 빨간공과 파란공의 위치가 겹치고 해당 위치가 O가 아닌 경우
		if (map[nry][nrx] != 'O' && map[nby][nbx] != 'O' && nry == nby && nrx == nbx)
		{
			// 이동 거리가 더 높은 공의 위치를 i 방향으로 한 칸 뒤로 빼준다
			if (rd > bd)
			{
				nry -= dy[i];
				nrx -= dx[i];
			}
			else
			{
				nby -= dy[i];
				nbx -= dx[i];
			}
		}

		if (!visit[nry][nrx][nby][nbx])
		{
			visit[nry][nrx][nby][nbx] = true;
			dfs(nry, nrx, nby, nbx, count + 1);
			visit[nry][nrx][nby][nbx] = false;
		}
	}
}

int main()
{
	cin >> n >> m;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> map[i][j];

			if (map[i][j] == 'R')
			{
				mry = i;
				mrx = j;
			}

			if (map[i][j] == 'B')
			{
				mby = i;
				mbx = j;
			}
		}
	}

	visit[mry][mrx][mby][mbx] = true;

	dfs(mry, mrx, mby, mbx, 0);

	if (ans == 100000) ans = -1;
	cout << ans << '\n';

	return 0;
}