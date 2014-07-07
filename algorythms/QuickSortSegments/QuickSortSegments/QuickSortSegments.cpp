#include <iostream>

void swap (int a[], int first, int second)
{
	int tmp;
	tmp = a[first];
	a[first] = a[second];
	a[second] = tmp;
}

int binSearch(int a[], int value, int n)
{
	int left = 0;
	int right = n - 1;
	int mid = 0;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (a[mid] == value)
		{
			return mid;
		}
		else if (a[mid] > value)
		{
			right = mid - 1;
			if (left == right)
			{
				return mid;
			}
		}
		else if (a[mid] < value)
		{
			left = mid + 1;
			if (left == right)
			{
				return mid;
			}
		}
	}

	return mid;
}

int segmentsCount(int value, int *begins, int *ends, int n)
{
	int result = 0;
	while ((begins[result] <= value) && (result < n))
	{
		++result;
	}
	
	int flag = 0;
	while ((ends[flag] < value) && (flag < n))
	{
		++flag;
		--result;
	}

	return result;
}

int partition(int a[], int left, int right)
{
	int x = a[left];
	int j = left;
	for (int i = left + 1; i <= right; ++i)
	{
		if (a[i] <= x)
		{
			swap(a, i, ++j);
		}
	}

	swap(a, left, j);
	return j;
}

void quickSort(int a[], int left, int right)
{
	if (left >= right)
	{
		return;
	}
	
	int mid = partition(a, left, right);
	quickSort(a, left, mid - 1);
	quickSort(a, mid + 1, right);
}

int main()
{
	int n = 0;
	int m = 0;
	std::cin >> n >> m;
	int *segmentsBegin = new int[n];
	int *segmentsEnd = new int[n];
	int element = 0;
	for (int i = 0; i < n; ++i)
	{
		std::cin >> segmentsBegin[i];// >> segmentsEnd[i];
	}

	quickSort(segmentsBegin, 0, n - 1);
	//quickSort(segmentsEnd, 0, n - 1);
	
	for (int i = 0; i < m; ++i)
	{
		std::cin >> element;
		std::cout << binSearch(segmentsBegin, element, n);
		//std::cout << segmentsCount(element, segmentsBegin, segmentsEnd, n) << " ";
	}

	delete[] segmentsBegin;
	delete[] segmentsEnd;
	return 0;
}