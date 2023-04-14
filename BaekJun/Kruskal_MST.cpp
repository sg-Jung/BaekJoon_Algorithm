#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 10000;

int parent[MAX]; // �� ����� �θ� ��带 �����ϴ� �迭
int sizes[MAX]; // ������ ũ�⸦ �����ϴ� �迭

// �ʱ�ȭ �Լ�
void init()
{
    // �ʱ� parent �迭�� �� ��尡 �ڱ� �ڽ��� �θ�� ����
    // size�� ���� 1�� �ʱ�ȭ
    for (int i = 0; i < MAX; i++)
    {
        parent[i] = i;
        sizes[i] = 1;
    }
}

// u�� ���� ������ ��Ʈ ��带 ã�� �Լ�
int collapsing_find(int u)
{
    int root = u;
    while (root != parent[root])
        root = parent[root];

    while (u != root)
    {
        int next = parent[u];
        parent[u] = root;
        u = next;
    }
    return root;
}

// �� ������ ��ġ�� �Լ� (����ġ�� ���� ������ ū ���տ� ���δ�)
void weighted_union(int u, int v)
{
    int root1 = collapsing_find(u);
    int root2 = collapsing_find(v);

    if (root1 == root2) return;
        
    if (sizes[root1] < sizes[root2])
    {
        parent[root1] = root2;
        sizes[root2] += sizes[root1];
    }
    else
    {
        parent[root2] = root1;
        sizes[root1] += sizes[root2];
    }
}

// ������ ����� �������� ������������ �����ϴ� �Լ�
bool cmp(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b)
{
    return a.first < b.first;
}

// Kruskal �˰���
vector<pair<int, pair<int, int>>> kruskal(vector<pair<int, pair<int, int>>> edges, int n)
{
    vector<pair<int, pair<int, int>>> mst;  // �ּ� ���� Ʈ��

    sort(edges.begin(), edges.end(), cmp); // �������� �������� ����

    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i].second.first;
        int v = edges[i].second.second;
        int cost = edges[i].first;

        // ����Ŭ�� �������� �ʴ� ������ ����
        if (collapsing_find(u) != collapsing_find(v))
        {
            weighted_union(u, v); // �� ������ ��ģ��
            mst.push_back(make_pair(cost, make_pair(u, v))); // ������ mst�� �߰�

            cout << "(" << u << ", " << v << "): ���� �߰���\n";
        }
        else
        {
            cout << "(" << u << ", " << v << "): ����Ŭ�� Ž����\n";
        }
        if (mst.size() == n - 1) break; // mst�� ũ�Ⱑ n-1�̸� ����
    }
    return mst;
}

int main()
{
    init(); // parent�� s �迭 �ʱ�ȭ
    cout << "***�׽�Ʈ ������ �Է�***\n";

    int n, m;
    cin >> n >> m;

    vector<pair<int, pair<int, int>>> edges(m); // �������� ������ ���� (����ġ, (����, ����))

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        int cost;
        cin >> cost;
        edges[i] = make_pair(cost, make_pair(u, v)); // ���� ���� ����
    }

    cout << "=======================================\n\n";
    cout << "***Kruskal ������***\n\n";

    vector<pair<int, pair<int, int>>> mst = kruskal(edges, n); // �ּ� ���� Ʈ�� ���
    
    cout << "=======================================\n\n";
   
    cout << "***�ּ� ���� Ʈ�� ���***\n";
    cout << "(����, ����): ����ġ\n\n";

    // �ּ� ���� Ʈ���� ���� ���� ���
    for (int i = 0; i < mst.size(); i++)
    {
        cout << "(" << mst[i].second.first << ", " << mst[i].second.second << "): " << mst[i].first <<"\n";
    }
    
    cout << "=======================================\n";

    return 0;
}