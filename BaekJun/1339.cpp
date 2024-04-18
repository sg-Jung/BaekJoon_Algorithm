#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 10

using namespace std;

int n;
vector<string> v(MAX_N);
int alphaNum[26];

int main()
{
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
	}


	for (int i = 0; i < v.size(); i++)
	{
		int c = 1;
		for (int j = v[i].size() - 1; j >= 0; j--)
		{
			alphaNum[v[i][j] - 'A'] += c;
			c *= 10;
		}
	}

	sort(alphaNum, alphaNum + 26, greater<>());

	int num = 9, ans = 0;
	for (int i = 0; i < 26; i++)
	{
		if (alphaNum[i] == 0) break;
		
		ans += alphaNum[i] * num--;
	}

	cout << ans << '\n';

	return 0;
}