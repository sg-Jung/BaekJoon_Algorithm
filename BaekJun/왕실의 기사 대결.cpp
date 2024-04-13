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
    // �ʱ�ȭ
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

        // dir �������� 1ĭ �̵��� �� r, c ��ǥ
        newK[x].first += dr[dir];
        newK[x].second += dc[dir];

        // �� ��ǥ�� �� ���̶�� false ��ȯ
        if (newK[x].first < 1 || newK[x].first + h[x] - 1 > L || newK[x].second < 1 || newK[x].second + w[x] - 1 > L)
            return false;

        // h, w �����ȿ� ������ �� üũ
        for (int i = newK[x].first; i <= newK[x].first + h[x] - 1; i++)
        {
            for (int j = newK[x].second; j <= newK[x].second + w[x] - 1; j++)
            {
                // ������ �ִ� ���
                if (board[i][j] == 1)
                {
                    dmg[x]++;
                }
                else if (board[i][j] == 2) // ���� �ִ� ��� false ��ȯ
                {
                    return false;
                }
            }
        }

        // �ٸ� ��� üũ
        for (int i = 1; i <= N; i++)
        {
            // �̹� ������ ����̰ų� ü���� ���� ����� continue
            if (is_moved[i] || hp[i] <= 0)
                continue;

            if (newK[x].first > knight[i].first + h[i] - 1 || knight[i].first > newK[x].first + h[x] - 1)
                continue;
            if (newK[x].second > knight[i].second + w[i] - 1 || knight[i].second > newK[x].second + w[x] - 1)
                continue;

            // ���� ���ǵ� ���� ó�� �������Ƿ� ���� ���ε��� �������� ����
            is_moved[i] = true;
            q.push(i);
        }
    }

    // ������ ��ɿ� ���� ����� ���� ������ ī��Ʈ �ߴµ�
    // ��ɿ� ���� �̵��� ���� ���ظ� ���� �ʱ� ������ 0���� ����
    dmg[index] = 0;

    return true; // �̻���� �Լ� ������ �Ϸ�Ǹ� ������ �� �ִ� ��Ȳ�̹Ƿ� true��ȯ
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