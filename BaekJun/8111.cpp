#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int t;
vector<int> arr(10);

void bfs(int n)
{
	vector<bool> visited(20001, false);
	queue<pair<int, string>> q;

	q.push(make_pair(1, "1"));
	visited[1] = true;

	while (!q.empty())
	{
		int x = q.front().first;
		string s = q.front().second;
		q.pop();

		if (x == 0)
		{
			cout << s << '\n';
			return;
		}

		int nx[2];
		string ns[2];

		nx[0] = (x * 10) % n;
		ns[0] = s + "0";
		nx[1] = (x * 10 + 1) % n;
		ns[1] = s + "1";

		for (int i = 0; i < 2; i++)
		{
			if (visited[nx[i]]) continue;
			visited[nx[i]] = true;
			q.push({ nx[i], ns[i] });
		}
	}

}

int main()
{
	cin >> t;

	for (int i = 0; i < t; i++)
	{
		cin >> arr[i];
		bfs(arr[i]);
	}

	return 0;
}