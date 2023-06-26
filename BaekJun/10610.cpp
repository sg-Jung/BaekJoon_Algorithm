#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
	string N;
	cin >> N;
	
	long long sum = 0;

	sort(N.begin(), N.end(), greater<>());

	for (auto& ch : N)
	{
		sum += ch - '0';
	}

	if (N[N.length() - 1] == '0' && sum % 3 == 0)
		cout << N;
	else
		cout << "-1";

	return 0;
}
