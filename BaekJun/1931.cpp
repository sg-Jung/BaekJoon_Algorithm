#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
	int n, start, end;
	cin >> n;

	vector<pair<int, int>> meet;

	for (int i = 0; i < n; i++)
	{
		cin >> start >> end;

		meet.push_back(make_pair(end, start));
	}

	sort(meet.begin(), meet.end());

	int time = 0;
	int count = 0;

	for (int i = 0; i < meet.size(); i++)
	{
		if (meet[i].second >= time)
		{
			time = meet[i].first;
			count++;
		}
	}

	cout << count;
	
	return 0;
}