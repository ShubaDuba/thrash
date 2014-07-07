#include <iostream>
#include <string.h>

void swap(int a[], int first, int second)
{
	int tmp = a[second];
	a[second] = a[first];
	a[first] = tmp;
}

void siftup(int a[], int counter)
{
	int flag = counter;
	int parent = (flag + 1) / 2 - 1;
	while ((flag > 0) && (a[flag] > a[parent]))
	{
		swap(a, flag, parent);
		flag = parent;
		parent = (flag + 1) / 2 - 1;
	}
}

void siftdown(int a[], int counter)
{
	if (counter == 0)
	{
		return;
	}
	int flag = 0;
	int rightChild = 2 * (flag + 1);
	int leftChild = rightChild - 1;
	while (((a[flag] < a[leftChild]) || (a[flag] < a[rightChild])) && (leftChild < counter))
	{
		if (rightChild == counter)
		{
			if (a[flag] < a[leftChild])
			{
				swap(a, flag, leftChild);
				flag = leftChild;
				rightChild = 2 * (flag + 1);
				leftChild = rightChild - 1;
			}
			else
			{
				return;
			}
		}
		else
		{
			if (a[leftChild] > a[rightChild])
			{
				swap(a, flag, leftChild);
				flag = leftChild;
				rightChild = 2 * (flag + 1);
				leftChild = rightChild - 1;
			}
			else
			{
				swap(a, flag, rightChild);
				flag = rightChild;
				rightChild = 2 * (flag + 1);
				leftChild = rightChild - 1;
			}
		}
	}
}

int extractMin(int a[], int *counter)
{
	int result = a[0];
	a[0] = a[--(*counter)];
	siftdown(a, *counter);
	return result;
}

void insertValue(int a[], int priority, int *counter)
{
	a[*counter] = priority;
	siftup(a, (*counter)++);
}

int main()
{
	int n = 0;
	std::cin >> n;
	int* arr = new int[n];
	char* tmp = new char[7];
	int value = 0;
	int counter = 0;

	for (int i = 0; i < n; ++i)
	{
		std::cin >> tmp;
		if (strcmp(tmp, "Insert") == 0)
		{
			std::cin >> value;
			insertValue(arr, value, &counter);
		}
		else if (strcmp(tmp, "Extract") == 0)
		{
			std::cout << extractMin(arr, &counter) << '\n';
		}
	}

	delete[] arr;
	return 0;
}

