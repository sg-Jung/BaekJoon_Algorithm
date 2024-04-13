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

    for (int sz = 2; sz <= n; sz++) // ���簢�� ���̴� 2���� ����, (1, 1)���� ����Ž������ ���簢���� ����
    {
        for (int r1 = 1; r1 <= n - sz + 1; r1++)
        {
            for (int c1 = 1; c1 <= n - sz + 1; c1++)
            {
                // (r1, c1): �»��, (r2, c2): ���ϴ�
                int r2 = r1 + sz - 1;
                int c2 = c1 + sz - 1;

                // ���� ���� Ż�ⱸ�� ���ٸ� continue
                if (e.first < r1 || e.first > r2 || e.second < c1 || e.second > c2)
                    continue;

                for (int num = 1; num <= m; num++)
                {
                    if (p[num] == e) continue; // �̹� Ż���� �÷��̾�� ����

                    int pr = p[num].first;
                    int pc = p[num].second;

                    if (pr < r1 || pr > r2 || pc < c1 || pc > c2) // �÷��̾ ���� ���̶�� continue
                        continue;
                    else // ���� ���̶�� dr, dc, len �� �Ҵ� �� �Լ� ����
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


    // k�� ���� �ݺ�
    for (int time = 1; time <= k; time++)
    {
        // �÷��̾� �̵�
        for (int num = 1; num <= m; num++)
        {
            // �̹� Ż���� �÷��̾��� continue
            if (p[num] == e)
                continue;

            int minDir = -1;
            int minDist = distance(p[num], e);

            for (int dir = 0; dir < 4; dir++)
            {
                pair<int, int> nrc;
                nrc.first = p[num].first + d_r[dir];
                nrc.second = p[num].second + d_c[dir];

                // ���ο� ��ǥ�� ���� ��� continue
                if (map[nrc.first][nrc.second] > 0)
                    continue;

                int dist = distance(nrc, e);

                if (dist < minDist)
                {
                    minDist = dist;
                    minDir = dir;
                }
            }

            // minDir�� -1�� �ƴ϶�� ������ �� �ִ� ������ ã�� �����̹Ƿ� player ��ġ ���� & �̵� �Ÿ� +1
            if (minDir != -1)
            {
                // �÷��̾� ��ǥ ���� �� map ����
                p[num].first += d_r[minDir];
                p[num].second += d_c[minDir];
                
                // �ش� �÷��̾��� moveCount +1
                ans++;
            }

        }

        // �÷��̾���� �� ������ �� ��� �÷��̾ Ż�ⱸ�� �ִٸ� break
        int exit_count = 0;
        for (int num = 1; num <= m; num++)
        {
            if (p[num] == e) exit_count++; // �÷��̾ Ż�ⱸ�� �ִٸ� exit_count ����
        }

        // exit_count�� �÷��̾��� ���ڰ� ���ٸ� ���� Ż���� ���̹Ƿ� �ݺ��� ����
        if (exit_count == m) break;


        // �÷��̾ ������ ���� ���� ���簢�� ���ϱ�
        findRect();

        // ���簢�� 90���� ������ �� 1�� ���ֱ�
        printf("dr, dc, len: %d, %d, %d\n", dr, dc, len);

        cout << "ȸ���ϱ� ��";
        printMap();

        // ���簢�� �� �� �� ����
        for (int i = dr; i < dr + len; i++)
        {
            for (int j = dc; j < dc + len; j++)
            {
                if (0 < map[i][j] && map[i][j] < 10) // ȸ���� ���� ���� ���� �ִٸ� �� �� -1
                {
                    map[i][j]--;
                }
            }
        }

        // �ð� �������� 90�� ȸ���Ͽ� map ����
        for (int i = dr; i < dr + len; i++)
        {
            for (int j = dc; j < dc + len; j++)
            {
                // (dr, dc) -> (0, 0)���� ��ȯ�� ����
                int zeroR = i - dr, zeroC = j - dc;
                // ��ȯ �� ���¿��� ȸ�� ������ ��ǥ�� (zeroR, zeroC) -> (zeroC, len - 1 - zeroR)�� �ȴ�
                int rotR = zeroC;
                int rotC = len - 1 - zeroR;
                
                // �ٽ� (0, 0) -> (dr, dc) ��ȯ�� ���� rotR, rotC�� dr, dc�� �� ����
                tmp[dr + rotR][dc + rotC] = map[i][j];
            }
        }

        // ȸ����Ų ������ map ����
        for (int i = dr; i < dr + len; i++)
        {
            for (int j = dc; j < dc + len; j++)
            {
                map[i][j] = tmp[i][j];
            }
        }

        // ���簢�� �� �÷��̾� ��ġ ����
        for (int num = 1; num <= m; num++)
        {
            int pr = p[num].first, pc = p[num].second;

            // �÷��̾ ���簢�� ���� ���̶�� continue
            if (pr < dr || pr >= dr + len || pc < dc || pc >= dc + len)
                continue;

            // (dr, dc) -> (0, 0)��ġ�� �ű�� ��ȯ�� �����ϸ�
            // (pr, pc)�� ���� �������� ��� ��ġ�� �ִ��� �� �� ����
            int zeroR = pr - dr, zeroC = pc - dc;

            // �ð� �������� 90�� ȸ��
            // (rotR, rotC)�� ���� �������� (pr, pc)�� 90�� ȸ���� ��ǥ
            int rotR = zeroC;
            int rotC = len - 1 - zeroR;

            // ȸ�� ��Ų ��ǥ�� �ٽ� (dr, dc) ��ġ�� �Ű��ֱ� ���� (rotR, rotC) + (dr, dc) ����
            p[num] = make_pair(dr + rotR, dc + rotC);
        }

        // ���簢�� �� Ż�ⱸ ��ġ ����
        int er = e.first;
        int ec = e.second;

        if (er >= dr && er < dr + len && ec >= dc && ec < dc + len)
        {
            // ���� �������� ����
            int zeroR = er - dr, zeroC = ec - dc;
            // 90�� ȸ��
            int rotR = zeroC, rotC = len - 1 - zeroR;
            // ȸ�� ��Ų ��ǥ�� �ٽ� (dr, dc) ���� ��ǥ�� ����
            e = make_pair(dr + rotR, dc + rotC);
        }
       
        cout << "ȸ�� ��";
        printMap();

        printf("Ż�ⱸ ��ǥ: %d, %d\n\n", e.first, e.second);
        // �� Ÿ�� ��
    }

    // �÷��̾��� �̵� �Ÿ� �� �ⱸ ��ǥ ���
    cout << ans << '\n';
    cout << e.first << ' ' << e.second << '\n';

    return 0;
}

// �� ������ �ٽ�: 
//
// �迭�� Ư�� �»�� ��ǥ���� �������� �迭�� ȸ�� ��ų ��
// �ش� ��ǥ�� ���� �������� �ű�� ȸ���� �°� ��ǥ�� ���� �� ��,
// �ٽ� ������ ��ǥ�� Ư�� �»�� ��ǥ���� �����ִ� ������� ���ؾ� ����
