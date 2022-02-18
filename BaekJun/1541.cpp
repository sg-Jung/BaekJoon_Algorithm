#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
	string sik;
	cin >> sik;

	string num;
	int ans = 0;
	bool isMinus = false;

	for (int i = 0; i < sik.size() + 1; i++)
	{
		if (sik[i] == '+' || sik[i] == '-' || i == sik.size())
		{
			if (isMinus)
			{
				ans -= stoi(num);
			}
			else
			{
				ans += stoi(num);
			}

			num = "";

			if (!isMinus && sik[i] == '-')
				isMinus = true;
		}
		else
		{
			num += sik[i];
		}

	}

	cout << ans;

	return 0;
}