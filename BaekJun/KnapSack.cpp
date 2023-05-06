#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void printList(vector<vector<int>>& D, int C, int n)
{
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= C; j++)
		{
			cout << D[i][j] << '\t';
		}
		cout << '\n';
	}
	cout << "\n\n";

}

int knapsack(int C, int n, vector<int>& weight, vector<int>& value)
{
	vector<vector<int>> D(n + 1, vector<int>(C + 1, 0));

	for (int i = 0; i <= n; i++) D[i][0] = 0;
	for (int w = 0; w <= C; w++) D[0][w] = 0;

	cout << "초기 배열" << '\n';
	printList(D, C, n);

	for (int i = 1; i <= n; i++)
	{
		for (int w = 1; w <= C; w++)
		{
			if (weight[i - 1] > w)
				D[i][w] = D[i - 1][w];
			else
				D[i][w] = max(D[i - 1][w], D[i - 1][w - weight[i - 1]] + value[i - 1]);
		}

		cout << "i = " << i << '\n';
		printList(D, C, n);
	}

	return D[n][C];
}

int main()
{
	int C = 10; // 배낭의 용량
	int n = 4; // 물건의 개수
	vector<int> weight = {5, 4, 6, 3}; // 무게
	vector<int> value = {10, 40, 30, 50 }; // 가치

	int result = knapsack(C, n, weight, value);

	cout << "result: " << result << '\n';

	return 0;
}