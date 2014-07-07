#include <iostream>

long long int merge (int a[], int l, int m, int r)
{
	long long int result = 0;
	int *tmp = new int[r - l + 1];
	int flag1 = l;
	int flag2 = m + 1;
	int flagTmp = 0;
	while ((flag1 <= m) && (flag2 <= r))
	{
		if (a[flag1] <= a[flag2])
		{
			tmp[flagTmp++] = a[flag1++];
		}
		else
		{
			tmp[flagTmp++] = a[flag2++];
			result += m - flag1 + 1;
		}
	}

	while (flag1 <= m)
	{
		tmp[flagTmp++] = a[flag1++];
	}

	while (flag2 <= r)
	{
		tmp[flagTmp++] = a[flag2++];
	}

	for (int i = l; i <= r; ++i)
	{
		a[i] = tmp[i - l];
	}

	delete[] tmp;
	return result;	
}

long long int inversions(int a[], int l, int r)
{
	long long int result = 0;
	if (l == r)
	{
		return 0;
	}

	int m = (l + r) / 2;
	result += inversions(a, l, m);
	result += inversions(a, m + 1, r);
	result += merge(a, l, m, r);
	return result;
}

int main()
{
	int n = 0;
	std::cin >> n;
	int *a = new int[n];
	for (int i = 0; i < n; ++i)
	{
		std::cin >> a[i];
	}
	
	std::cout << inversions(a, 0, n - 1);
	delete[] a;
	return 0;
}