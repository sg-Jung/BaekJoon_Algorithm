#include<iostream>
#include<vector>
#include<stack>

using namespace std;

int N, M, S; // N: ��� ��, M: ���� ��, S: ���� ���

vector<int> graph[1001];
bool visited[1001] = { false, };
stack<int> st;

/* ��� �Լ��� �̿��� dfs*/
void dfs(int v) // v: ���
{
	if (visited[v]) return; // �̹� �湮�ߴٸ� ����

	visited[v] = true;
	cout << v << "\n";

	// ���� ��� ��������� ȣ��
	for (int i = 0; i < graph[v].size(); i++)
	{
		int next = graph[v][i];
		dfs(next);
	}
}

/* Stack�� �̿��� dfs*/
void dfs2(int v)
{
	st.push(v); // ��Ʈ ��� ����

	while (!st.empty())
	{
		int cur = st.top();
		st.pop();

		if (visited[cur]) continue; // �̹� �湮�� ����� ���
		visited[cur] = true;

		cout << cur << "\n";

		// ���ڰ� ���� ��� ���� �湮�ϱ� ���� reverse
		for (int i = graph[cur].size() - 1; i >= 0; i--)
		{
			int next = graph[cur][i];
			st.push(next);
		}

		//// ���ڰ� ū ��� ���� �湮
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

	fill_n(visited, 1001, false); // �湮 ���� �ʱ�ȭ
	cout << "\n\n";

	dfs2(1);

	return 0;
}