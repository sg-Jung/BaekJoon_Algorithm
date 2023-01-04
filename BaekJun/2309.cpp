#include <iostream>
#include <vector>
#include <algorithm>

#define N 9

using namespace std;

int A[N];

int main()
{
	int sum = 0;

	for (int i = 0; i < N; i++)
	{
		cin >> A[i];
		sum += A[i];
	}

	sort(A, A + N);

	for (int i = 0; i < N - 1; i++)
		for (int j = i + 1; j < N; j++)
		{
			if ((sum - A[i] - A[j]) == 100)
			{
				for (int k = 0; k < N; k++)
				{
					if (k == i || k == j)
						continue;
					cout << A[k] << endl;
				}
				return 0;
			}

		}

	return 0;
}