#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

int n = 5;
int map[5][5];
int dx[4] = {0, -1, 0, 1}; // �� �� �� ��
int dy[4] = {1, 0, -1, 0};
//vector<string> res;
set<string> res;

void dfs(int x, int y, int len, string cur)
{
	if (len == 5)
	{
		//res.push_back(cur);
		res.insert(cur);
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		int newX = x + dx[i], newY = y + dy[i];
		if ((newX >= 0 && newY >= 0) && (newX < n && newY < n)) dfs(newX, newY, len + 1, cur + to_string(map[newX][newY]));
	}
}

int main()
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> map[i][j];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			dfs(i, j, 0, to_string(map[i][j]));

	// vector ��� �� �ߺ��� ���Ÿ� ���� �ڵ�, set�� �ߺ����� ������� �ʴ� stl�� insert�� �ڵ����� �ߺ����� ���ܽ�Ų��
	//sort(res.begin(), res.end());
	//res.erase(unique(res.begin(), res.end()), res.end());

	cout << res.size() << '\n';

	return 0;
}
