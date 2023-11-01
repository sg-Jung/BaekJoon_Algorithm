#include<iostream>
#include<vector>
#include<stack>

using namespace std;

int N, M, S; // N: 노드 수, M: 간선 수, S: 시작 노드

vector<int> graph[1001];
bool visited[1001] = { false, };
stack<int> st;

/* 재귀 함수를 이용한 dfs*/
void dfs(int v) // v: 노드
{
	visited[v] = true;
	cout << v << "\n";

	// 인접 노드 재귀적으로 호출
	for (int i = 0; i < graph[v].size(); i++)
	{
		int next = graph[v][i];
		if (!visited[next]);
			dfs(next);
	}
}

/* Stack을 이용한 dfs*/
void dfs2(int v)
{
	st.push(v); // 루트 노드 삽입

	while (!st.empty())
	{
		int cur = st.top();
		st.pop();

		if (visited[cur]) continue; // 이미 방문한 노드라면 통과
		visited[cur] = true;

		cout << cur << "\n";

		// 숫자가 작은 노드 먼저 방문하기 위해 reverse
		for (int i = graph[cur].size() - 1; i >= 0; i--)
		{
			int next = graph[cur][i];
			st.push(next);
		}

		//// 숫자가 큰 노드 먼저 방문
		//for (int i = 0; i < graph[cur].size(); i++)
		//{
		//	int next = graph[cur][i];
		//	st.push(next);
		//}
	}
}

int main()
{
	graph[1].push_back(2);
	graph[1].push_back(3);
	graph[1].push_back(8);

	graph[2].push_back(1);
	graph[2].push_back(7);

	graph[3].push_back(1);
	graph[3].push_back(4);
	graph[3].push_back(5);

	graph[4].push_back(3);
	graph[4].push_back(5);

	graph[5].push_back(3);
	graph[5].push_back(4);

	graph[6].push_back(7);

	graph[7].push_back(2);
	graph[7].push_back(6);
	graph[7].push_back(8);

	graph[8].push_back(1);
	graph[8].push_back(7);
	
	dfs(1);

	fill_n(visited, 1001, false); // 방문 여부 초기화
	cout << "\n\n";

	dfs2(1);

	return 0;
}
