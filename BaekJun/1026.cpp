#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
	int n, temp;
	cin >> n;

	vector<int> A = vector<int>();
	vector<int> B = vector<int>();

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> temp;

			if (i == 0)
				A.push_back(temp);
			else
				B.push_back(temp);
		}
	}

	sort(A.begin(), A.end());

	sort(B.begin(), B.end());
	reverse(B.begin(), B.end());

	int ans = 0;

	for (int i = 0; i < n; i++)
	{
		ans += A[i] * B[i];
	}

	cout << ans;

	return 0;
}