#include<iostream>
#include<vector>
#include<queue>

using namespace std;

vector<int> graph[1001];
bool visited[1001] = { false, };
queue<int> que;

void bfs(int v)
{
	que.push(v); // 루트 노드 삽입

	while (!que.empty())
	{
		int cur = que.front();
		que.pop();

		if (visited[cur]) continue;
		visited[cur] = true;

		cout << cur << "\n";

		// 인접 노드들 삽입
		for (int i = 0; i < graph[cur].size(); i++)
		{
			int next = graph[cur][i];
			que.push(next);
		}
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

	bfs(1);

	return 0;
}