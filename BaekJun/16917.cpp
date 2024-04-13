#include <iostream>
#include <string>

using namespace std;

int main()
{
	int A, B, C, X, Y;
	cin >> A >> B >> C >> X >> Y;

	long long answer = A * X + B * Y;
	for (int i = 1; i <= max(X, Y); i++)
	{
		int price = 2 * i * C + max(X - i, 0) * A + max(Y - i, 0) * B;
		if (price < answer) answer = price;
	}

	cout << answer << '\n';

	return 0;
}