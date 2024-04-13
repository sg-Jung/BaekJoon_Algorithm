#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int n, h, w, ans;
vector<pair<int, int>> st(1001);
bool used[1001];


bool isPossible(int r1, int c1, int r2, int c2)
{
	if (r1 + r2 <= h && max(c1, c2) <= w) return true;
	if (max(r1, r2) <= h && c1 + c2 <= w) return true;
	return false;
}

bool isFour(int r1, int c1, int r2, int c2)
{
	if (isPossible(r1, c1, r2, c2)) return true;
	if (isPossible(c1, r1, r2, c2)) return true;
	if (isPossible(r1, c1, c2, r2)) return true;
	if (isPossible(c1, r1, c2, r2)) return true;
	return false;
}

void Calc(vector<int>& comb)
{
	int r1 = st[comb[0]].first, c1 = st[comb[0]].second, r2 = st[comb[1]].first, c2 = st[comb[1]].second;

	if (isFour(r1, c1, r2, c2))
	{
		ans = max(ans, r1 * c1 + r2 * c2);
	}
}

void Comb(vector<int>& arr, vector<int>& comb, int r, int index)
{
	if (r == 0)
	{
		Calc(comb);
		return;
	}

	for (int i = index; i < arr.size(); i++)
	{
		if (!used[i])
		{
			comb.push_back(arr[i]);
			used[i] = true;
			Comb(arr, comb, r - 1, i);
			comb.pop_back();
			used[i] = false;
		}
	}
}

int main()
{
	cin >> h >> w;
	cin >> n;
	vector<int> index, comb;

	for (int i = 0; i < n; i++)
	{
		cin >> st[i].first;
		cin >> st[i].second;
		index.push_back(i);
	}

	Comb(index, comb, 2, 0);

	cout << ans << endl;

	return 0;
}