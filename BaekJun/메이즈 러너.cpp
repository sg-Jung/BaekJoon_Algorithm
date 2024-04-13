#include <iostream>
#include <cmath>
#include <algorithm>

#define MAX_N 11
#define MAX_M 11

using namespace std;

int n, m, k, ans;
int map[MAX_N][MAX_N], tmp[MAX_N][MAX_N];

int d_r[4] = { -1, 1, 0, 0 };
int d_c[4] = { 0, 0, -1, 1 };

int dr, dc, len;

pair<int, int> p[MAX_M];
pair<int, int> e;

void printMap()
{
    cout << endl;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            printf("%3d", map[i][j]);
        }
        cout << endl;
    }
    cout << endl;
}

int distance(pair<int, int> a, pair<int, int> b)
{
    return abs(a.first - b.first) + abs(a.second - b.second);
}

void findRect()
{
    bool is_InPlayer = false;

    for (int sz = 2; sz <= n; sz++) // 정사각형 길이는 2부터 시작, (1, 1)부터 완전탐색으로 정사각형을 구함
    {
        for (int r1 = 1; r1 <= n - sz + 1; r1++)
        {
            for (int c1 = 1; c1 <= n - sz + 1; c1++)
            {
                // (r1, c1): 좌상단, (r2, c2): 우하단
                int r2 = r1 + sz - 1;
                int c2 = c1 + sz - 1;

                // 범위 내에 탈출구가 없다면 continue
                if (e.first < r1 || e.first > r2 || e.second < c1 || e.second > c2)
                    continue;

                for (int num = 1; num <= m; num++)
                {
                    if (p[num] == e) continue; // 이미 탈출한 플레이어는 제외

                    int pr = p[num].first;
                    int pc = p[num].second;

                    if (pr < r1 || pr > r2 || pc < c1 || pc > c2) // 플레이어가 범위 밖이라면 continue
                        continue;
                    else // 범위 안이라면 dr, dc, len 값 할당 후 함수 종료
                    {
                        dr = r1;
                        dc = c1;
                        len = sz;

                        return;
                    }
                }
            }
        }
    }
}

int main()
{
    cin >> n >> m >> k;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> map[i][j];
        }
    }

    for (int i = 1; i <= m; i++)
    {
        int r, c;
        cin >> r >> c;
        p[i] = { r, c };
    }

    cin >> e.first >> e.second;


    // k초 동안 반복
    for (int time = 1; time <= k; time++)
    {
        // 플레이어 이동
        for (int num = 1; num <= m; num++)
        {
            // 이미 탈출한 플레이어라면 continue
            if (p[num] == e)
                continue;

            int minDir = -1;
            int minDist = distance(p[num], e);

            for (int dir = 0; dir < 4; dir++)
            {
                pair<int, int> nrc;
                nrc.first = p[num].first + d_r[dir];
                nrc.second = p[num].second + d_c[dir];

                // 새로운 좌표가 벽인 경우 continue
                if (map[nrc.first][nrc.second] > 0)
                    continue;

                int dist = distance(nrc, e);

                if (dist < minDist)
                {
                    minDist = dist;
                    minDir = dir;
                }
            }

            // minDir이 -1이 아니라면 움직일 수 있는 방향을 찾은 상태이므로 player 위치 변경 & 이동 거리 +1
            if (minDir != -1)
            {
                // 플레이어 좌표 변경 및 map 갱신
                p[num].first += d_r[minDir];
                p[num].second += d_c[minDir];
                
                // 해당 플레이어의 moveCount +1
                ans++;
            }

        }

        // 플레이어들이 다 움직인 후 모든 플레이어가 탈출구에 있다면 break
        int exit_count = 0;
        for (int num = 1; num <= m; num++)
        {
            if (p[num] == e) exit_count++; // 플레이어가 탈출구에 있다면 exit_count 증가
        }

        // exit_count와 플레이어의 숫자가 같다면 전부 탈출한 것이므로 반복문 종료
        if (exit_count == m) break;


        // 플레이어를 포함한 가장 작은 정사각형 구하기
        findRect();

        // 정사각형 90도로 돌리고 벽 1씩 빼주기
        printf("dr, dc, len: %d, %d, %d\n", dr, dc, len);

        cout << "회전하기 전";
        printMap();

        // 정사각형 내 벽 값 갱신
        for (int i = dr; i < dr + len; i++)
        {
            for (int j = dc; j < dc + len; j++)
            {
                if (0 < map[i][j] && map[i][j] < 10) // 회전된 범위 내에 벽이 있다면 벽 값 -1
                {
                    map[i][j]--;
                }
            }
        }

        // 시계 방향으로 90도 회전하여 map 갱신
        for (int i = dr; i < dr + len; i++)
        {
            for (int j = dc; j < dc + len; j++)
            {
                // (dr, dc) -> (0, 0)으로 변환을 진행
                int zeroR = i - dr, zeroC = j - dc;
                // 변환 한 상태에서 회전 이후의 좌표가 (zeroR, zeroC) -> (zeroC, len - 1 - zeroR)이 된다
                int rotR = zeroC;
                int rotC = len - 1 - zeroR;
                
                // 다시 (0, 0) -> (dr, dc) 변환을 위해 rotR, rotC에 dr, dc를 더 해줌
                tmp[dr + rotR][dc + rotC] = map[i][j];
            }
        }

        // 회전시킨 값으로 map 갱신
        for (int i = dr; i < dr + len; i++)
        {
            for (int j = dc; j < dc + len; j++)
            {
                map[i][j] = tmp[i][j];
            }
        }

        // 정사각형 내 플레이어 위치 변경
        for (int num = 1; num <= m; num++)
        {
            int pr = p[num].first, pc = p[num].second;

            // 플레이어가 정사각형 범위 밖이라면 continue
            if (pr < dr || pr >= dr + len || pc < dc || pc >= dc + len)
                continue;

            // (dr, dc) -> (0, 0)위치로 옮기는 변환을 수행하면
            // (pr, pc)가 원점 기준으로 어느 위치에 있는지 알 수 있음
            int zeroR = pr - dr, zeroC = pc - dc;

            // 시계 방향으로 90도 회전
            // (rotR, rotC)는 원점 기준으로 (pr, pc)가 90도 회전한 좌표
            int rotR = zeroC;
            int rotC = len - 1 - zeroR;

            // 회전 시킨 좌표를 다시 (dr, dc) 위치로 옮겨주기 위해 (rotR, rotC) + (dr, dc) 수행
            p[num] = make_pair(dr + rotR, dc + rotC);
        }

        // 정사각형 내 탈출구 위치 변경
        int er = e.first;
        int ec = e.second;

        if (er >= dr && er < dr + len && ec >= dc && ec < dc + len)
        {
            // 원점 기준으로 변경
            int zeroR = er - dr, zeroC = ec - dc;
            // 90도 회전
            int rotR = zeroC, rotC = len - 1 - zeroR;
            // 회전 시킨 좌표를 다시 (dr, dc) 기준 좌표로 변경
            e = make_pair(dr + rotR, dc + rotC);
        }
       
        cout << "회전 후";
        printMap();

        printf("탈출구 좌표: %d, %d\n\n", e.first, e.second);
        // 한 타임 끝
    }

    // 플레이어의 이동 거리 및 출구 좌표 출력
    cout << ans << '\n';
    cout << e.first << ' ' << e.second << '\n';

    return 0;
}

// 이 문제의 핵심: 
//
// 배열의 특정 좌상단 좌표값을 기준으로 배열을 회전 시킬 때
// 해당 좌표를 원점 기준으로 옮기고 회전에 맞게 좌표를 변경 한 후,
// 다시 변경한 좌표에 특정 좌상단 좌표값을 더해주는 방식으로 구해야 쉽다
