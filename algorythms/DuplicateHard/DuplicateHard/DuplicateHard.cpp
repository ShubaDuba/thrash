#include <iostream>
#include <stdio.h>

int main()
{
	int n;
	std::cin >> n;
	int *arr = new int[n];
	for (int i = 0; i < n; ++i)
	{
		std::cin >> arr[i];
	}

	int k = n - 1;
	int j = n - 1;

	do
	{
		k = arr[k];
		j = arr[arr[j]];
	}
	while (k != j);

	j = n - 1;
	do
	{
		k = arr[k];
		j = arr[j];
	}
	while (k != j);

	std::cout << k;

	return 0;
}

