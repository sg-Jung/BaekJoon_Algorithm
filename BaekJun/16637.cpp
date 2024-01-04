#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string su;
int N;
int answer = -2147000000;

// su = 3+8*7-9*2, N = 9

int Calc(int a, int b, char op)
{
	if (op == '+') return a + b;
	else if (op == '-') return a - b;
	else if (op == '*') return a * b;
}

void dfs(int idx, int res)
{
	if (idx >= N)
	{
		answer = max(answer, res);
		return;
	}

	char op = idx == 0 ? '+' : su[idx - 1];
	
	dfs(idx + 2, Calc(res, su[idx] - '0', op));

	if (idx + 2 < N)
	{
		int bracket = Calc(su[idx] - '0', su[idx + 2] - '0', su[idx + 1]);
		dfs(idx + 4, Calc(res, bracket, op));
	}

}

int main()
{
	cin >> N;
	cin >> su;

	dfs(0, 0);

	cout << answer << endl;
	return 0;
}