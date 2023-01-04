#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int E, S, M;
	cin >> E >> S >> M;

	int e = 1, s = 1, m = 1;
	int i = 1;

	while (true)
	{
		if (E == e && S == s && M == m)
		{
			cout << i << endl;
			break;
		}

		e++;
		s++;
		m++;

		if (e > 15)
			e = 1;
		if (s > 28)
			s = 1;
		if (m > 19)
			m = 1;

		i++;
	}

	return 0;
}