#include <iostream>

int binSearchinSorted(int *arr, int n, int k)
{
	int l = 0;
	int r = n - 1;
	int m = (l + r) / 2;
	while (l <= r)
	{
		if (arr[m] == k)
		{
			return m;
		}
		else if (arr[m] < k)
		{
			l = m + 1;
		}
		else
		{
			r = m - 1;
		}

		m = (l + r) / 2;
	}

	return -1;
}

int main()
{
	int n = 0;
	std::cin >> n;
	int *input = new int[n];
	for (int i = 0; i < n; ++i)
	{
		std::cin >> input[i];
	}

	int k = 0;
	std::cin >> k;
	int *sought = new int[k];
	for (int i = 0; i < k; ++i)
	{
		std::cin >> sought[i];
	}

	for (int i = 0; i < k; ++i)
	{
		std::cout << binSearchinSorted(input, n, sought[i]) << " ";
	}

	return 0;
}
