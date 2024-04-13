#include <iostream>
#include <algorithm>
#include <queue>
#include <cmath>

// ��Ÿ�� �и� �� ���������� ó���ϴ� �κ��� ������ ��������

using namespace std;

int n, m, p, c, d;
pair<int, int> rudolf;
pair<int, int> santa[31];
bool is_live[31];
int score[31], stun[31];
int board[51][51];

int rDy[8] = { -1,  0,  1,  1,  1,  0, -1, -1 };
int rDx[8] = { -1, -1, -1,  0,  1,  1,  1,  0 };

// �� �� �� ��
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

    // ��Ÿ�� knockDamage��ŭ �з���
    newSantaPose.first += dy[dir] * knockDamage * knockDir;
    newSantaPose.second += dx[dir] * knockDamage * knockDir;

    int originSantaY = santa[knockSanta].first, originSantaX = santa[knockSanta].second;
    int newSantaY = newSantaPose.first, newSantaX = newSantaPose.second;

    // �з��� ��ǥ�� �� ���̶�� ��� ó��
    if (newSantaY < 1 || newSantaY > n || newSantaX < 1 || newSantaX > n)
    {
        is_live[knockSanta] = false;
        board[originSantaY][originSantaX] = 0;
    }
    else // �� ���̶�� ��Ÿ ��ġ ����
    {
        if (board[newSantaY][newSantaX] == 0) // ���� ����
        {
            // ���ο� ��ġ�� ��Ÿ ����
            board[originSantaY][originSantaX] = 0;
            board[newSantaY][newSantaX] = knockSanta;
            santa[knockSanta] = newSantaPose;
            return;
        }
        else if (board[newSantaY][newSantaX] > 0) // �з��� ��Ÿ ��ġ�� �ٸ� ��Ÿ�� �ִ� ���
        {
            knockBackSanta(board[newSantaY][newSantaX], dir, dy, dx, 1, knockDir); // 1ĭ �˹�
            
            // ���ο� ��ġ�� ��Ÿ ����
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
        // �絹�� �浹
        // ��� ��Ÿ�� �Ÿ� ����ϸ� �ּұ����� ��Ÿ�� ���Ѵ�
        // => �ּұ��̰� �� �� �̻��� ��� -> 1. r��ǥ�� ū ��Ÿ 2. c��ǥ�� ū ��Ÿ�� �켱����
        // 8���� �� �ش� ��Ÿ�� �Ÿ��� ���� ����� �������� �̵�
        // �̵� �� ��Ÿ�� �浹�ߴٸ� �ش� ��Ÿ���� +C���� and �絹���� �̵��������� C��ŭ �з���


        // ���� ���۽� ���� Ƚ�� ���ҽ�����
        for (int curSanta = 1; curSanta <= p; curSanta++)
        {
            if (stun[curSanta] > 0)
            {
                stun[curSanta]--;
            }
        }
        

        // �ּұ����� ��Ÿ ���
        double minDist = 100000;
        int minSantaNum = 0;

        for (int num = 1; num <= p; num++)
        {
            // ���� ��Ÿ��� continue
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

                // dist == minDist�� ���
                if (santa[num].first >= santa[minSantaNum].first)
                {
                    if (santa[num].first > santa[minSantaNum].first)
                    {
                        minSantaNum = num;
                        continue;
                    }
                    else // r�� ���� ���
                    {
                        if (santa[num].second > santa[minSantaNum].second)
                        {
                            minSantaNum = num;
                        }
                    }
                }
            }
        }

        // �ּұ��� ��Ÿ ��� ��

        // 8���� �� �ش� ��Ÿ�� ���� ����� �Ÿ� ���

        pair<int, int> newRudolf;
        int minDir = -1;
        minDist = 100000;

        for (int dir = 0; dir < 8; dir++)
        {
            int ny = rudolf.first + rDy[dir];
            int nx = rudolf.second + rDx[dir];
            pair<int, int> temp;

            if (ny < 1 || ny > n || nx < 1 || nx > n) continue; // ���� ���̹Ƿ� continue

            temp.first = ny, temp.second = nx;

            double dist = distance(temp, santa[minSantaNum]);

            if (dist < minDist)
            {
                minDist = dist;
                minDir = dir;
                newRudolf = temp;
            }
        }

        // 8���� �� ��Ÿ�� ���� ����� ��ġ ��� �� (newRudolf)
        
        // �ش� ��ġ�� ��Ÿ�� �ִ��� üũ �� ��Ÿ�� �ִٸ� �ش� ��Ÿ���� +C�� ��
        // �絹���� ������ �������� C��ŭ �з���
        if (board[newRudolf.first][newRudolf.second] == minSantaNum)
        {
            pair<int, int> newSantaPose = santa[minSantaNum];
            score[minSantaNum] += c;
            stun[minSantaNum] = 2; // stun�� (���� round + 2)��°�� Ǯ���Ƿ� +2

            knockBackSanta(minSantaNum, minDir, rDy, rDx, c, 1);
        }

        // ������ �絹�� ��ġ ���� �� �絹�� ��ǥ ����
        board[rudolf.first][rudolf.second] = 0;
        board[newRudolf.first][newRudolf.second] = -1;
        rudolf = newRudolf;

        cout << "\n\nround: " << round << " Rudolf End\n";
        printBoard();
        
        
// ======================================================================================================================
        // ��Ÿ ���

        for (int curSanta = 1; curSanta <= p; curSanta++)
        {
            // Ż�� or ���� ����
            // ��Ÿ�� �׾��ų� ���ϻ��¶�� continue
            if (!is_live[curSanta] || stun[curSanta] > 0) continue;


            // �絹���� ���� ����� �Ÿ� �� ���� ���

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

            // �絹���� ���� ����� �Ÿ� �� ���� ��� ��


            // �ش� ��ġ�� �絹���� �ִ��� �˻�
            // �絹���� �ִٸ� ��Ÿ ���� +D and ��Ÿ�� ������ ��ġ�� �ݴ� �������� ��Ÿ�� Dĭ �и�
            // �и� �� ���� ���̶�� Ż�� ó��

            // ��Ÿ�� ���ο� ��ġ�� �絹���� �ִ� ���
            if (board[newSantaPose.first][newSantaPose.second] == -1)
            {
                score[curSanta] += d;
                stun[curSanta] = 2; // stun�� (���� round + 2)��°�� Ǯ���Ƿ� +2

                // ���� ��Ÿ ��ġ �ʱ�ȭ & ��Ÿ ��ġ ����
                board[curSantaPose.first][curSantaPose.second] = 0;
                santa[curSanta] = newSantaPose;

                knockBackSanta(curSanta, minDir, sDy, sDx, d, -1);
            }
            else // ���ο� ��ġ�� �絹���� ���� ���
            {
                // ���� �� ����
                board[curSantaPose.first][curSantaPose.second] = 0;
                board[newSantaPose.first][newSantaPose.second] = curSanta;
                
                // ��Ÿ ��ġ ����
                santa[curSanta] = newSantaPose;
            }
        }

        cout << "\n\nround: " << round << " Santa End\n";
        printBoard();

        // �� ������ ����ִ� ��Ÿ���� +1��
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

        // ��� ����̶�� ��� ��������
        if (dieCount == p) break;
    }


    // ���� ���� ���
    for (int i = 1; i <= p; i++)
    {
        cout << score[i] << ' ';
    }

    return 0;
}