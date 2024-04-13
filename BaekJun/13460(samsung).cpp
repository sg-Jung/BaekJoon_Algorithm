#include <iostream>

using namespace std;

int n, m, ans = 100000;

char map[11][11];
bool visit[11][11][11][11];
int mry, mrx, mby, mbx;

// ��, ��, ��, ��
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

	if (map[by][bx] == 'O') return; // �Ķ����� O�� ��ġ�ߴٸ� �Լ�����
	if (map[ry][rx] == 'O') // �������� O�� ��ġ�ߴٸ� ans ���
	{
		ans = min(ans, count);
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		int nry = ry, nrx = rx, nby = by, nbx = bx, rd = 0, bd = 0;

		move(nry, nrx, rd, i); // ������ # or O ������ ���� �̵� & �̵��Ÿ� rd�� üũ
		move(nby, nbx, bd, i); // �Ķ��� # or O ������ ���� �̵� & �̵��Ÿ� bd�� üũ

		// �������� �Ķ����� ��ġ�� ��ġ�� �ش� ��ġ�� O�� �ƴ� ���
		if (map[nry][nrx] != 'O' && map[nby][nbx] != 'O' && nry == nby && nrx == nbx)
		{
			// �̵� �Ÿ��� �� ���� ���� ��ġ�� i �������� �� ĭ �ڷ� ���ش�
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