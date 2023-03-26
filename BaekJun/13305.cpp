#define _CRT_SECURE_NO_WARNINGS
#include<iostream>

using namespace std;

int dist[100000];
int cost[100000];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	cin >> N;

	long long sum = 0;
	long long cur_cost;

	for (int i = 0; i < N - 1; i++)
		cin >> dist[i];

	for (int i = 0; i < N; i++)
		cin >> cost[i];

	cur_cost = cost[0];
	sum += cur_cost * dist[0];

	for (int i = 1; i < N - 1; i++)
	{
		if (cur_cost < cost[i])
		{
			sum += cur_cost * dist[i];
		}
		else
		{
			cur_cost = cost[i];
			sum += cur_cost * dist[i];
		}
	}

	cout << sum << '\n';

	return 0;
}