#include <iostream>
#include <vector>

using namespace std;

#define MAX 1000000

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	vector<long long> d(MAX + 1, 1);

	for (int i = 2; i <= MAX; i++)
		for (int j = 1; i * j <= MAX; j++)
		{
			d[i * j] += i;
		}

	vector<long long>s(MAX + 1);

	for (int i = 1; i < MAX + 1; i++)
	{
		s[i] = s[i - 1] + d[i];
	}

	int t;
	cin >> t;

	while (t--)
	{
		int n;
		cin >> n;
		cout << s[n] << '\n';
	}

	return 0;
}