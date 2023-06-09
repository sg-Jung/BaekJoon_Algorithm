#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

vector<int> graph[1001];
bool visited[1001] = { false, };

void DFS(int V) // 재귀 방식
{
	if (visited[V]) return;

	visited[V] = true;
	cout << V << " ";

	for (int i = 0; i < graph[V].size(); i++)
		DFS(graph[V][i]);
}

void DFS2(int V) // stack 방식
{
	stack<int> st;

	st.push(V);

	while (!st.empty())
	{
		int top = st.top();
		st.pop();

		if (visited[top]) continue; // 이미 방문한 노드라면 통과
		
		visited[top] = true;
		cout << top << " ";

		for (int i = graph[top].size() - 1; i >= 0; i--)
		{
			int next = graph[top][i];
			st.push(next);
		}
	}
}

void BFS(int V)
{
	queue<int> qu;

	qu.push(V);

	while (!qu.empty())
	{
		int cur = qu.front();
		qu.pop();

		if (visited[cur]) continue;
		
		visited[cur] = true;
		cout << cur << " ";

		for (int i = 0; i < graph[cur].size(); i++)
		{
			int next = graph[cur][i];
			qu.push(next);
		}
	}
}

int main()
{
	int N, M, V;
	cin >> N >> M >> V;

	int v1, v2;

	for (int i = 0; i < M; i++)
	{
		cin >> v1 >> v2;
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
	}

	for(int i = 1; i <= N; i++)
		sort(graph[i].begin(), graph[i].end());

	DFS2(V);
	
	cout << "\n";
	fill_n(visited, 1001, false);

	BFS(V);
	cout << "\n";

	return 0;
}