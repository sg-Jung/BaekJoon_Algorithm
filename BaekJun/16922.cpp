#include <iostream>
#include <string>

using namespace std;

bool check[1001];
int roma[4] = { 1, 5, 10, 50 };
int N;

void dfs(int count, int index, int sum)
{
	if (count == N)
	{
		check[sum] = true;
		return;
	}

	for (int i = index; i < 4; i++)
	{
		dfs(count + 1, i, sum + roma[i]);
	}
}

int main()
{
	cin >> N;
	
	dfs(0, 0, 0);

	int ans = 0;
	for (int i = 0; i < 1001; i++)
	{
		if (check[i]) ans++;
	}
	cout << ans << '\n';

	return 0;
}