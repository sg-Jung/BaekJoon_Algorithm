#include <iostream>
#include <vector>

using namespace std;

// 왼쪽, 아래, 오른쪽, 위
int dy[4] = {0, 1, 0, -1};
int dx[4] = {-1, 0, 1, 0};

int N = 5;
vector<vector<int>> board(N, vector<int>(N, 0));


// 홀수길이 2차원 배열의 중심에서 시작하여 방향을 바꾸며 이동(혹은 탐색)을 하는데, 방향을 2번 바꿀 때마다 이동 거리가 1씩 증가하는 형식의 알고리즘

void init_grid()
{
	// y좌표, x좌표, 이동 방향, 이동 횟수, 값, 이동 거리
	int y, x, dir, moveCount, value, dist;

	y = x = N / 2; // 배열의 중앙부터 값이 들어가므로 x, y에 배열의 중앙값 대입

	dir = moveCount = value = 0; // 이동 방향, 이동 횟수, 값 초기화

	dist = 1; // 이동 거리는 1부터 시작

	while (true)
	{
		for (int i = 0; i < dist; i++) // dist만큼 dir방향으로 이동
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			// 이동한 좌표가 (0, -1)인 경우 배열의 마지막 좌표이므로 함수 종료
			// (배열의 길이가 홀수면 항상 마지막 좌표는 (0, -1), 방향은 서쪽)
			if (0 == ny && -1 == nx)
			{
				return;
			}

			// 배열에 들어갈 값 증가, 대입
			value++;
			board[ny][nx] = value;

			// x, y 좌표 갱신
			y = ny;
			x = nx;
		}

		moveCount++; // 움직인 횟수
		dir = (dir + 1) % 4; // 방향 변경

		// 어느 방향이든 2번 이동한 경우
		if (2 == moveCount)
		{
			dist++; // 이동거리 증가
			moveCount = 0; // 이동횟수 초기화
		}
	}
}


void print_board()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%3d", board[i][j]);
		}
		cout << '\n';
	}
}

int main()
{
	init_grid();
	print_board();

	return 0;
}