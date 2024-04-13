#include <iostream>
#include <queue>
#include <cstring>

#define MAX_N 21
using namespace std;

// 상어 (y, x), 크기, 먹은 물고기 수
int sy, sx, sharkSize, eatCount;
int n, map[MAX_N][MAX_N];

// 최소 거리의 물고기(y, x), 걸린 시간
int fy, fx, t;

int dist[MAX_N][MAX_N];
bool visit[MAX_N][MAX_N];

// 상 하 좌 우
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

			// 새로운 좌표가 맵 밖이라면 continue
			if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
			// 새로운 좌표에 상어 크기보다 큰 물고기가 있거나 방문한 곳이라면 continue
			if (map[ny][nx] > sharkSize || visit[ny][nx]) continue;

			// 방문 처리 및 이동거리 갱신
			visit[ny][nx] = true;
			dist[ny][nx] = dist[curY][curX] + 1;

			// 새로운 좌표가 물고기 위치라면 반복문 탈출
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
	// 값 초기화
	int minDist = 10000;
	fy = -1;
	fx = -1;

	// 좌상단부터 순서대로 탐색하기 때문에 (y가 작은것 우선, x가 작은것 우선) 조건 만족
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int fishSize = map[i][j];

			// 아기 상어 위치이므로 continue
			if (i == sy && j == sx) continue;

			// 물고기 크기가 0보다 크고 상어 크기보다 작은 것에 대해서만 확인
			if (0 < fishSize && fishSize < sharkSize)
			{
				int curDist = distanceBFS(i, j); // 움직일 수 있는 칸이 없는 경우 -1 반환

				if ((curDist < minDist) && -1 != curDist)
				{
					minDist = curDist;
					fy = i;
					fx = j;
				}
			}
		}
	}

	// fy, fx 둘다 -1이라면 찾은 물고기가 없으므로 false 반환
	if (-1 == fy && -1 == fx)
	{
		return false;
	}
	else
	{
		t += minDist;
		map[fy][fx] = 0;

		// 상어 위치 갱신
		sy = fy;
		sx = fx;

		eatCount++;
		// eatCount와 상어의 크기가 같다면, 상어 크기 1증가 및 eatCount 0으로 초기화
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
	// 아기 상어의 좌표를 알고 있으니 map은 0으로 초기화
	map[sy][sx] = 0;

	while (1)
	{
		// 크기가 작은 물고기 중 가장 가까이 있는 물고기 찾는데, false를 반환하면 찾은 물고기가 없는 것이므로 반복문 종료
		if (!findMinDistanceFish()) break;
	}

	cout << t << '\n';

	return 0;
}