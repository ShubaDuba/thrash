#include <iostream>

bool frequentExist(int arr[], int n)
{
	int tmp = 0; 
	int *frequent = NULL;

	for (int i = 0; i < n; ++i) 
	{
		if (tmp == 0)
		{
			frequent = arr + i;
			tmp++;
		}
		else if (*frequent == arr[i])
		{
			tmp++;
		}
		else
		{
			tmp--;
		}
	}

	if (tmp == 0)
	{
		return false;
	}
	else
	{
		int count = 0;
		for (int i = 0; i < n; ++i)
		{
			if (arr[i] == *frequent)
			{
				++count;
			}
		}

		return (count > (n / 2));
	}
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

	if (frequentExist(a, n))
	{
		std::cout << "True";
	}
	else
	{
		std::cout << "False";
	}

	delete[] a;
	return 0;
}



