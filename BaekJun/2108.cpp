#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int n;
vector<double> arr;
int cnt[8001];


int main()
{
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		int num;
		
		cin >> num;
		arr.push_back(num);

		if (num < 0)
		{
			int ab = abs(num);
			cnt[4000 + ab]++;
		}
		else
		{
			cnt[num]++;
		}
	}

	sort(arr.begin(), arr.end());

	double avg = 0;

	for (int i = 0; i < n; i++)
	{
		avg += arr[i];
	}

	avg = round(avg / n);

	if (avg == -0)
	{
		avg = 0;
	}

	double mid = 0;

	if (n == 1)
	{
		mid = arr[0];
	}
	else
	{
		mid = arr[arr.size() / 2];
	}

	vector<int> v;

	double bin = 0, maxCount = 0;

	for (int i = 0; i < 8001; i++)
	{
		maxCount = max(maxCount, (double)cnt[i]);
	}

	for (int i = 0; i < 8001; i++)
	{
		if (cnt[i] == maxCount)
		{
			if (i > 4000)
			{
				v.push_back((i - 4000) * (-1));
			}
			else
			{
				v.push_back(i);
			}
		}
	}

	sort(v.begin(), v.end());
	
	if (v.size() == 1)
	{
		bin = v[0];
	}
	else
	{
		bin = v[1];
	}

	double range = 0;
	range = arr[n - 1] - arr[0];

	cout << avg << endl;
	cout << mid << endl;
	cout << bin << endl;
	cout << range << endl;

	return 0;
}