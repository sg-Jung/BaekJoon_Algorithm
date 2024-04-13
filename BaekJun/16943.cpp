#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

string A, B;
bool used[1001];
int ans = -1;

void Permutation(string& A, string& C, int r)
{
	if (r == 0)
	{
		if (C[0] == '0') return;

		int Bnum = stoi(B);
		int Cnum = stoi(C);

		if (Cnum < Bnum) ans = max(ans, Cnum);

		return;
	}

	for (int i = 0; i < A.size(); i++)
	{
		if (!used[i])
		{
			used[i] = true;
			C.push_back(A[i]);
			Permutation(A, C, r - 1);
			C.pop_back();
			used[i] = false;
		}
	}
}

int main()
{
	cin >> A >> B;
	string C;

	Permutation(A, C, A.size());

	cout << ans << endl;
	return 0;
}