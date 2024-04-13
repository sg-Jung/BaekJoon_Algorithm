#include <iostream>
#include <queue>
#include <cstring>

#define MAX_N 21
using namespace std;

// ��� (y, x), ũ��, ���� ����� ��
int sy, sx, sharkSize, eatCount;
int n, map[MAX_N][MAX_N];

// �ּ� �Ÿ��� �����(y, x), �ɸ� �ð�
int fy, fx, t;

int dist[MAX_N][MAX_N];
bool visit[MAX_N][MAX_N];

// �� �� �� ��
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

int distanceBFS(int fy, int fx)
{
	memset(visit, false, sizeof(visit));
	memset(dist, 0, sizeof(dist));
	queue<pair<int, int>> q;

	q.push({ sy, sx });
	visit[sy][sx] = true;

	while (!q.empty())
	{
		pair<int, int> curPose = q.front();
		q.pop();

		int curY = curPose.first;
		int curX = curPose.second;

		for (int dir = 0; dir < 4; dir++)
		{
			int ny = curY + dy[dir];
			int nx = curX + dx[dir];

			// ���ο� ��ǥ�� �� ���̶�� continue
			if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
			// ���ο� ��ǥ�� ��� ũ�⺸�� ū ����Ⱑ �ְų� �湮�� ���̶�� continue
			if (map[ny][nx] > sharkSize || visit[ny][nx]) continue;

			// �湮 ó�� �� �̵��Ÿ� ����
			visit[ny][nx] = true;
			dist[ny][nx] = dist[curY][curX] + 1;

			// ���ο� ��ǥ�� ����� ��ġ��� �ݺ��� Ż��
			if (ny == fy && nx == fx)
			{
				return dist[ny][nx];
			}

			q.push(make_pair(ny, nx));
		}
	}

	return -1;
}

bool findMinDistanceFish()
{
	// �� �ʱ�ȭ
	int minDist = 10000;
	fy = -1;
	fx = -1;

	// �»�ܺ��� ������� Ž���ϱ� ������ (y�� ������ �켱, x�� ������ �켱) ���� ����
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int fishSize = map[i][j];

			// �Ʊ� ��� ��ġ�̹Ƿ� continue
			if (i == sy && j == sx) continue;

			// ����� ũ�Ⱑ 0���� ũ�� ��� ũ�⺸�� ���� �Ϳ� ���ؼ��� Ȯ��
			if (0 < fishSize && fishSize < sharkSize)
			{
				int curDist = distanceBFS(i, j); // ������ �� �ִ� ĭ�� ���� ��� -1 ��ȯ

				if ((curDist < minDist) && -1 != curDist)
				{
					minDist = curDist;
					fy = i;
					fx = j;
				}
			}
		}
	}

	// fy, fx �Ѵ� -1�̶�� ã�� ����Ⱑ �����Ƿ� false ��ȯ
	if (-1 == fy && -1 == fx)
	{
		return false;
	}
	else
	{
		t += minDist;
		map[fy][fx] = 0;

		// ��� ��ġ ����
		sy = fy;
		sx = fx;

		eatCount++;
		// eatCount�� ����� ũ�Ⱑ ���ٸ�, ��� ũ�� 1���� �� eatCount 0���� �ʱ�ȭ
		if (eatCount == sharkSize)
		{
			sharkSize += 1;
			eatCount = 0;
		}
		return true;
	}
}


int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> map[i][j];

			if (map[i][j] == 9)
			{
				sy = i;
				sx = j;
				sharkSize = 2;
				eatCount = 0;
			}
		}
	}
	// �Ʊ� ����� ��ǥ�� �˰� ������ map�� 0���� �ʱ�ȭ
	map[sy][sx] = 0;

	while (1)
	{
		// ũ�Ⱑ ���� ����� �� ���� ������ �ִ� ����� ã�µ�, false�� ��ȯ�ϸ� ã�� ����Ⱑ ���� ���̹Ƿ� �ݺ��� ����
		if (!findMinDistanceFish()) break;
	}

	cout << t << '\n';

	return 0;
}