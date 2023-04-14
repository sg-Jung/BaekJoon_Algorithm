#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 10000;

int parent[MAX]; // 각 노드의 부모 노드를 저장하는 배열
int sizes[MAX]; // 집합의 크기를 저장하는 배열

// 초기화 함수
void init()
{
    // 초기 parent 배열은 각 노드가 자기 자신을 부모로 갖음
    // size는 전부 1로 초기화
    for (int i = 0; i < MAX; i++)
    {
        parent[i] = i;
        sizes[i] = 1;
    }
}

// u가 속한 집합의 루트 노드를 찾는 함수
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

// 두 집합을 합치는 함수 (가중치가 작은 집합을 큰 집합에 붙인다)
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

// 간선의 비용을 기준으로 오름차순으로 정렬하는 함수
bool cmp(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b)
{
    return a.first < b.first;
}

// Kruskal 알고리즘
vector<pair<int, pair<int, int>>> kruskal(vector<pair<int, pair<int, int>>> edges, int n)
{
    vector<pair<int, pair<int, int>>> mst;  // 최소 신장 트리

    sort(edges.begin(), edges.end(), cmp); // 간선들을 비용순으로 정렬

    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i].second.first;
        int v = edges[i].second.second;
        int cost = edges[i].first;

        // 사이클을 형성하지 않는 간선만 선택
        if (collapsing_find(u) != collapsing_find(v))
        {
            weighted_union(u, v); // 두 정점을 합친다
            mst.push_back(make_pair(cost, make_pair(u, v))); // 간선을 mst에 추가

            cout << "(" << u << ", " << v << "): 간선 추가됨\n";
        }
        else
        {
            cout << "(" << u << ", " << v << "): 사이클이 탐지됨\n";
        }
        if (mst.size() == n - 1) break; // mst의 크기가 n-1이면 종료
    }
    return mst;
}

int main()
{
    init(); // parent와 s 배열 초기화
    cout << "***테스트 데이터 입력***\n";

    int n, m;
    cin >> n >> m;

    vector<pair<int, pair<int, int>>> edges(m); // 간선들을 저장할 벡터 (가중치, (정점, 정점))

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        int cost;
        cin >> cost;
        edges[i] = make_pair(cost, make_pair(u, v)); // 간선 정보 저장
    }

    cout << "=======================================\n\n";
    cout << "***Kruskal 계산시작***\n\n";

    vector<pair<int, pair<int, int>>> mst = kruskal(edges, n); // 최소 신장 트리 계산
    
    cout << "=======================================\n\n";
   
    cout << "***최소 신장 트리 출력***\n";
    cout << "(정점, 정점): 가중치\n\n";

    // 최소 신장 트리의 간선 정보 출력
    for (int i = 0; i < mst.size(); i++)
    {
        cout << "(" << mst[i].second.first << ", " << mst[i].second.second << "): " << mst[i].first <<"\n";
    }
    
    cout << "=======================================\n";

    return 0;
}