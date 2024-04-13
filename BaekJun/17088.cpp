#include <iostream>
#include <vector>

using namespace std;

int n, answer = -1;
vector<int> B;

void Check(int change)
{
	if (answer == -1 || answer > change) answer = change;
}

void dfs(int a, int b, int idx, int change)
{
	if (idx == B.size())
	{
		Check(change);
		return;
	}

	int r = b - a;

	if(B[idx] - b == r) dfs(b, B[idx], idx + 1, change);
	else if (B[idx] + 1 - b == r) dfs(b, B[idx] + 1, idx + 1, change + 1);
	else if (B[idx] - 1 - b == r) dfs(b, B[idx] - 1, idx + 1, change + 1);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	B.resize(n);
	for (int i = 0; i < n; i++)
		cin >> B[i];

	if (n == 1) 
	{
		cout << 0 << endl;
		return 0;
	}

	dfs(B[0], B[1], 2, 0);
	dfs(B[0], B[1] - 1, 2, 1);
	dfs(B[0], B[1] + 1, 2, 1);

	dfs(B[0] - 1, B[1], 2, 1);
	dfs(B[0] - 1, B[1] - 1, 2, 2);
	dfs(B[0] - 1, B[1] + 1, 2, 2);

	dfs(B[0] + 1, B[1], 2, 1);
	dfs(B[0] + 1, B[1] - 1, 2, 2);
	dfs(B[0] + 1, B[1] + 1, 2, 2);

	if (answer == 2147483647) answer = -1;
	cout << answer << '\n';

	return 0;
}