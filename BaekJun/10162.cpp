#define _CRT_SECURE_NO_WARNINGS
#include<iostream>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T;
	cin >> T;

	int a = 300, b = 60, c = 10;
	int a1, b1, c1;

	a1 = T / a;
	T %= a;
	b1 = T / b;
	T %= b;
	c1 = T / c;
	T %= c;

	if (T == 0)
		cout << a1 << " " << b1 << " " << c1 << '\n';
	else
		cout << "-1\n";

	return 0;
}