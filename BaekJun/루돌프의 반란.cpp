#include <iostream>
#include <algorithm>
#include <queue>
#include <cmath>

// 산타가 밀릴 때 연쇄적으로 처리하는 부분이 문제임 ㅈ같은거

using namespace std;

int n, m, p, c, d;
pair<int, int> rudolf;
pair<int, int> santa[31];
bool is_live[31];
int score[31], stun[31];
int board[51][51];

int rDy[8] = { -1,  0,  1,  1,  1,  0, -1, -1 };
int rDx[8] = { -1, -1, -1,  0,  1,  1,  1,  0 };

// 상 우 하 좌
int sDy[4] = { -1, 0, 1,  0 };
int sDx[4] = { 0,  1, 0, -1 };

double distance(pair<int, int>& a, pair<int, int>& b)
{
    return pow(a.first - b.first, 2) + pow(a.second - b.second, 2);
}

void printBoard()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << board[i][j] << "    ";
        }
        cout << '\n';
    }

    cout << '\n';

    cout << "live: ";
    for (int i = 1; i <= p; i++)
    {
        cout << is_live[i] << ' ';
    }
    cout << '\n';

    cout << "stun: ";
    for (int i = 1; i <= p; i++)
    {
        cout << stun[i] << ' ';
    }
    cout << '\n';

    cout << "score: ";
    for (int i = 1; i <= p; i++)
    {
        cout << score[i] << ' ';
    }
    cout << '\n';
}


void knockBackSanta(int knockSanta, int dir, int* dy, int* dx, int knockDamage, int knockDir)
{
    pair<int, int> newSantaPose = santa[knockSanta];

    // 산타가 knockDamage만큼 밀려남
    newSantaPose.first += dy[dir] * knockDamage * knockDir;
    newSantaPose.second += dx[dir] * knockDamage * knockDir;

    int originSantaY = santa[knockSanta].first, originSantaX = santa[knockSanta].second;
    int newSantaY = newSantaPose.first, newSantaX = newSantaPose.second;

    // 밀려난 좌표가 맵 밖이라면 사망 처리
    if (newSantaY < 1 || newSantaY > n || newSantaX < 1 || newSantaX > n)
    {
        is_live[knockSanta] = false;
        board[originSantaY][originSantaX] = 0;
    }
    else // 맵 안이라면 산타 위치 변경
    {
        if (board[newSantaY][newSantaX] == 0) // 종료 조건
        {
            // 새로운 위치로 산타 갱신
            board[originSantaY][originSantaX] = 0;
            board[newSantaY][newSantaX] = knockSanta;
            santa[knockSanta] = newSantaPose;
            return;
        }
        else if (board[newSantaY][newSantaX] > 0) // 밀려난 산타 위치에 다른 산타가 있는 경우
        {
            knockBackSanta(board[newSantaY][newSantaX], dir, dy, dx, 1, knockDir); // 1칸 넉백
            
            // 새로운 위치로 산타 갱신
            board[newSantaY][newSantaX] = knockSanta;
            santa[knockSanta] = newSantaPose;
        }
    }
}

int main()
{
    cin >> n >> m >> p >> c >> d;
    cin >> rudolf.first >> rudolf.second;
    board[rudolf.first][rudolf.second] = -1;


    for (int i = 0; i < p; i++)
    {
        int num;
        cin >> num;
        cin >> santa[num].first >> santa[num].second;
        board[santa[num].first][santa[num].second] = num;
        is_live[num] = true;
    }

    cout << "\ninit board\n";
    printBoard();

    cout << "======================\n\n";

    for (int round = 1; round <= m; round++)
    {
        // 루돌프 충돌
        // 모든 산타와 거리 계산하며 최소길이의 산타를 구한다
        // => 최소길이가 두 명 이상일 경우 -> 1. r좌표가 큰 산타 2. c좌표가 큰 산타가 우선순위
        // 8방향 중 해당 산타와 거리가 가장 가까운 방향으로 이동
        // 이동 후 산타와 충돌했다면 해당 산타에게 +C점수 and 루돌프의 이동방향으로 C만큼 밀려남


        // 라운드 시작시 스턴 횟수 감소시켜줌
        for (int curSanta = 1; curSanta <= p; curSanta++)
        {
            if (stun[curSanta] > 0)
            {
                stun[curSanta]--;
            }
        }
        

        // 최소길이의 산타 계산
        double minDist = 100000;
        int minSantaNum = 0;

        for (int num = 1; num <= p; num++)
        {
            // 죽은 산타라면 continue
            if (!is_live[num]) continue;


            double dist = distance(rudolf, santa[num]);

            if (dist <= minDist)
            {
                if (dist < minDist)
                {
                    minDist = dist;
                    minSantaNum = num;
                    continue;
                }

                // dist == minDist인 경우
                if (santa[num].first >= santa[minSantaNum].first)
                {
                    if (santa[num].first > santa[minSantaNum].first)
                    {
                        minSantaNum = num;
                        continue;
                    }
                    else // r이 같은 경우
                    {
                        if (santa[num].second > santa[minSantaNum].second)
                        {
                            minSantaNum = num;
                        }
                    }
                }
            }
        }

        // 최소길이 산타 계산 끝

        // 8방향 중 해당 산타와 가장 가까운 거리 계산

        pair<int, int> newRudolf;
        int minDir = -1;
        minDist = 100000;

        for (int dir = 0; dir < 8; dir++)
        {
            int ny = rudolf.first + rDy[dir];
            int nx = rudolf.second + rDx[dir];
            pair<int, int> temp;

            if (ny < 1 || ny > n || nx < 1 || nx > n) continue; // 범위 밖이므로 continue

            temp.first = ny, temp.second = nx;

            double dist = distance(temp, santa[minSantaNum]);

            if (dist < minDist)
            {
                minDist = dist;
                minDir = dir;
                newRudolf = temp;
            }
        }

        // 8방향 중 산타와 가장 가까운 위치 계산 끝 (newRudolf)
        
        // 해당 위치에 산타가 있는지 체크 후 산타가 있다면 해당 산타에게 +C점 후
        // 루돌프가 움직인 방향으로 C만큼 밀려남
        if (board[newRudolf.first][newRudolf.second] == minSantaNum)
        {
            pair<int, int> newSantaPose = santa[minSantaNum];
            score[minSantaNum] += c;
            stun[minSantaNum] = 2; // stun은 (현재 round + 2)번째에 풀리므로 +2

            knockBackSanta(minSantaNum, minDir, rDy, rDx, c, 1);
        }

        // 보드의 루돌프 위치 변경 및 루돌프 좌표 갱신
        board[rudolf.first][rudolf.second] = 0;
        board[newRudolf.first][newRudolf.second] = -1;
        rudolf = newRudolf;

        cout << "\n\nround: " << round << " Rudolf End\n";
        printBoard();
        
        
// ======================================================================================================================
        // 산타 계산

        for (int curSanta = 1; curSanta <= p; curSanta++)
        {
            // 탈락 or 기절 제외
            // 산타가 죽었거나 스턴상태라면 continue
            if (!is_live[curSanta] || stun[curSanta] > 0) continue;


            // 루돌프와 가장 가까운 거리 및 방향 계산

            pair<int, int> newSantaPose = santa[curSanta], curSantaPose = santa[curSanta];
            minDir = -1;
            minDist = distance(curSantaPose, rudolf);

            for (int dir = 0; dir < 4; dir++)
            {
                int ny = curSantaPose.first + sDy[dir];
                int nx = curSantaPose.second + sDx[dir];
                pair<int, int> newPose = {ny, nx};
                
                if (ny < 1 || ny > n || nx < 1 || nx > n || board[ny][nx] > 0)
                    continue;

                double dist = distance(newPose, rudolf);
                
                if (dist < minDist)
                {
                    minDist = dist;
                    minDir = dir;
                    newSantaPose = newPose;
                }
            }

            // 루돌프와 가장 가까운 거리 및 방향 계산 끝


            // 해당 위치에 루돌프가 있는지 검사
            // 루돌프가 있다면 산타 점수 +D and 산타가 움직인 위치의 반대 방향으로 산타가 D칸 밀림
            // 밀린 후 보드 밖이라면 탈락 처리

            // 산타의 새로운 위치에 루돌프가 있는 경우
            if (board[newSantaPose.first][newSantaPose.second] == -1)
            {
                score[curSanta] += d;
                stun[curSanta] = 2; // stun은 (현재 round + 2)번째에 풀리므로 +2

                // 현재 산타 위치 초기화 & 산타 위치 갱신
                board[curSantaPose.first][curSantaPose.second] = 0;
                santa[curSanta] = newSantaPose;

                knockBackSanta(curSanta, minDir, sDy, sDx, d, -1);
            }
            else // 새로운 위치에 루돌프가 없는 경우
            {
                // 보드 값 변경
                board[curSantaPose.first][curSantaPose.second] = 0;
                board[newSantaPose.first][newSantaPose.second] = curSanta;
                
                // 산타 위치 갱신
                santa[curSanta] = newSantaPose;
            }
        }

        cout << "\n\nround: " << round << " Santa End\n";
        printBoard();

        // 매 턴이후 살아있는 산타에게 +1점
        int dieCount = 0;
        for (int s = 1; s <= p; s++)
        {
            if (is_live[s])
            {
                score[s]++;
            }
            else
            {
                dieCount++;
            }
        }

        // 모두 사망이라면 즉시 게임종료
        if (dieCount == p) break;
    }


    // 최종 점수 출력
    for (int i = 1; i <= p; i++)
    {
        cout << score[i] << ' ';
    }

    return 0;
}