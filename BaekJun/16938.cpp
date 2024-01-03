#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

int n, L, R, X; // L <= sum <= R, problems[problems.size() - 1] - problems[0] >= X
int answer;
bool used[1001];

void Combination(vector<int>& rank, vector<int>& problems, int r, int index)
{
	if (r == 0)
	{
		vector<int> temp = problems;
		sort(temp.begin(), temp.end());
		int sum = accumulate(temp.begin(), temp.end(), 0);

		if (((L <= sum) && (sum <= R)) && temp[temp.size() - 1] - temp[0] >= X)
			answer++;
		
		return;
	}

	for (int i = index; i < rank.size(); i++)
	{
		if (!used[i])
		{
			used[i] = true;
			problems.push_back(rank[i]);
			Combination(rank, problems, r - 1, i);
			problems.pop_back();
			used[i] = false;
		}
	}
}

int main()
{
	cin >> n >> L >> R >> X;
	vector<int> rank(n), problems;

	for (int i = 0; i < n; i++)
		cin >> rank[i];

	for (int i = 2; i <= n; i++)
	{
		Combination(rank, problems, i, 0);
	}

	cout << answer << '\n';

	return 0;
}