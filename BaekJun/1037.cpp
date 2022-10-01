#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	int count, temp, min, max;
	vector<int> arr;

	cin >> count;

	for (int i = 0; i < count; i++)
	{
		cin >> temp;
		arr.push_back(temp);
	}

	max = *max_element(arr.begin(), arr.end());
	min = *min_element(arr.begin(), arr.end());

	cout << max * min << "\n";
	return 0;
}