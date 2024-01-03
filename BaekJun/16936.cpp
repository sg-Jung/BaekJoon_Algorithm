#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;


int main()
{
	int n;
	cin >> n;
	vector<pair<int, long long>> b(n);

	for (int i = 0; i < n; i++)
	{
		long long num;
		cin >> num;
		b[i].second = num;

		while (num % 3 == 0)
		{
			b[i].first++;
			num /= 3;
		}
		b[i].first = -b[i].first;
	}

	sort(b.begin(), b.end());

	for (int i = 0; i < n; i++)
		cout << b[i].second << " ";
	cout << '\n';

	return 0;
}