#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int n, m, ans = 0;
bool used[1001];
vector<int> arr;
unordered_map<int, vector<int>> map;

bool DontMix()
{
	for (int i = 0; i < arr.size(); i++)
	{
		if (map.find(arr[i]) == map.end()) continue;

		for (auto& num : map[arr[i]])
		{
			if (find(arr.begin(), arr.end(), num) != arr.end()) return true;
		}
	}

	return false;
}

void Combination(int r, int index)
{
	if (r == arr.size())
	{
		if(!DontMix())
			ans++;
		
		return;
	}

	for (int i = index; i <= n; i++)
	{
		if (!used[i])
		{
			used[i] = true;
			arr.push_back(i);
			Combination(r, i);
			arr.pop_back();
			used[i] = false;
		}
	}
}

int main()
{
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int key, value;
		cin >> key >> value;
		map[key].push_back(value);
	}

	Combination(3, 1);

	cout << ans << '\n';

	return 0;
}