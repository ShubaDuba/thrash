#include <iostream>

int main() {
	int n = 0;
	std::cin >> n;
	int *arr = new int[10];
	for (int i = 0; i < 10; ++i)
	{
		arr[i] = 0;
	}

	int tmp = 0;
	for (int i = 0; i < n; ++i)
	{		
		std::cin >> tmp;
		++arr[tmp];
	}
	
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < arr[i]; ++j)
		{
			std::cout << i <<" ";
		}
	}

	delete[] arr;
	return 0;
}