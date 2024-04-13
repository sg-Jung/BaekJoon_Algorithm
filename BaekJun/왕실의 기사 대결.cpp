#include <iostream>
#include <queue>

using namespace std;

int L, N, Q;
int board[41][41];
int hp[31], b_hp[31];
int ans = 0;

pair<int, int> knight[31];
pair<int, int> newK[31];
int h[31], w[31], dmg[31];

bool is_moved[31];

int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0, -1 };

bool TryMovement(int index, int dir)
{
    // 초기화
    for (int i = 1; i <= N; i++)
    {
        is_moved[i] = false;
        newK[i] = knight[i];
        dmg[i] = 0;
    }

    queue<int> q;

    q.push(index);
    is_moved[index] = true;

    while (!q.empty())
    {
        int x = q.front();
        q.pop();

        // dir 방향으로 1칸 이동한 새 r, c 좌표
        newK[x].first += dr[dir];
        newK[x].second += dc[dir];

        // 새 좌표가 맵 밖이라면 false 반환
        if (newK[x].first < 1 || newK[x].first + h[x] - 1 > L || newK[x].second < 1 || newK[x].second + w[x] - 1 > L)
            return false;

        // h, w 범위안에 함정과 벽 체크
        for (int i = newK[x].first; i <= newK[x].first + h[x] - 1; i++)
        {
            for (int j = newK[x].second; j <= newK[x].second + w[x] - 1; j++)
            {
                // 함정이 있는 경우
                if (board[i][j] == 1)
                {
                    dmg[x]++;
                }
                else if (board[i][j] == 2) // 벽이 있는 경우 false 반환
                {
                    return false;
                }
            }
        }

        // 다른 기사 체크
        for (int i = 1; i <= N; i++)
        {
            // 이미 움직인 기사이거나 체력이 없는 기사라면 continue
            if (is_moved[i] || hp[i] <= 0)
                continue;

            if (newK[x].first > knight[i].first + h[i] - 1 || knight[i].first > newK[x].first + h[x] - 1)
                continue;
            if (newK[x].second > knight[i].second + w[i] - 1 || knight[i].second > newK[x].second + w[x] - 1)
                continue;

            // 예외 조건들 전부 처리 해줬으므로 다음 라인들은 범위안의 기사들
            is_moved[i] = true;
            q.push(i);
        }
    }

    // 위에서 명령에 의한 기사의 함정 개수도 카운트 했는데
    // 명령에 의해 이동한 기사는 피해를 입지 않기 때문에 0으로 설정
    dmg[index] = 0;

    return true; // 이상없이 함수 동작이 완료되면 움직일 수 있는 상황이므로 true반환
}

int main()
{
    cin >> L >> N >> Q;

    for (int i = 1; i <= L; i++)
    {
        for (int j = 1; j <= L; j++)
        {
            cin >> board[i][j];
        }
    }

    for (int i = 1; i <= N; i++)
    {
        cin >> knight[i].first >> knight[i].second >> h[i] >> w[i] >> hp[i];
        b_hp[i] = hp[i];
    }

    for (int order = 1; order <= Q; order++)
    {
        int idx, dir;
        cin >> idx >> dir;

        if (hp[idx] <= 0) continue;

        if (TryMovement(idx, dir))
        {
            for (int i = 1; i <= N; i++)
            {
                knight[i] = newK[i];
                hp[i] -= dmg[i];
            }
        }
    }

    for (int i = 1; i <= N; i++)
    {
        if (hp[i] > 0)
            ans += b_hp[i] - hp[i];
    }

    cout << ans << '\n';
    return 0;
}