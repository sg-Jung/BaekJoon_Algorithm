#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <sstream>

using namespace std;

int t;

deque<int> split(string str, char del)
{
	istringstream iss(str);
	string buf;

	deque<int> result;

	while (getline(iss, buf, del))
	{
		result.push_back(stoi(buf));
	}

	return result;
}

bool D(deque<int>& arr, bool& isReverse)
{
	if (arr.size() == 0)
		return false;

	if (isReverse)
	{
		arr.pop_back();
	}
	else
	{
		arr.pop_front();
	}
	return true;
}

int main()
{
	cin >> t;

	for (int test_case = 0; test_case < t; test_case++)
	{
		string p;
		cin >> p;

		// 수행할 함수 vector에 대입
		vector<char> vP;
		for (auto ch : p)
			vP.push_back(ch);


		// 배열 할당
		int n;
		string arrString;
		cin >> n >> arrString;

		arrString.erase(arrString.begin());
		arrString.pop_back();

		deque<int> arr = split(arrString, ',');
		bool isErr = false;
		bool isReverse = false;
		
		// 함수 수행
		for (auto& ch : vP)
		{
			if (ch == 'R')
			{
				isReverse = !isReverse;
			}
			else if (ch == 'D')
			{
				if (!D(arr, isReverse))
				{
					cout << "error" << '\n';
					isErr = true;
					break;
				}
			}
		}

		if (!isErr)
		{
			int arrSize = arr.size();

			if (!isReverse)
			{
				cout << '[';
				for (auto iter = arr.begin(); iter != arr.end(); iter++)
				{
					if (iter == arr.end() - 1)
					{
						cout << *iter;
						break;
					}
					cout << *iter << ",";
				}
				cout << "]\n";
			}
			else
			{
				cout << '[';
				for (auto iter = arr.rbegin(); iter != arr.rend(); iter++)
				{
					if (iter == arr.rend() - 1)
					{
						cout << *iter;
						break;
					}
					cout << *iter << ",";
				}
				cout << "]\n";
			}
		}
	}

	return 0;
}