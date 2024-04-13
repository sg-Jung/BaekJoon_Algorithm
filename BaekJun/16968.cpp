#include <iostream>
#include <string>

using namespace std;

int main()
{
	string N;
	cin >> N;
	int answer = 1;
	int num;

	for (int i = 0; i < N.size(); i++)
	{
		num = (N[i] == 'd' ? 10 : 26);
		if (N[i] == N[i + 1] && i < N.size() - 1)
			num--;
		answer *= num;
	}

	cout << answer << endl;

	return 0;
}