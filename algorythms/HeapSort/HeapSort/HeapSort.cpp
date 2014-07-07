#include <iostream>
#include <string.h>

void swap(int a[], int first, int second)
{
	int tmp = a[second];
	a[second] = a[first];
	a[first] = tmp;
}

void siftDown(int a[], int counter, int num)
{
	int leftChild = counter * 2 + 1;
	int rightChild = counter * 2 + 2;
	if (leftChild > num - 1)
	{
		return;
	}
	else if ((rightChild > num - 1) && (a[leftChild] > a[counter]))
	{
		swap(a, leftChild, counter);
		siftDown(a, leftChild, num);
	}
	else if (rightChild <= num - 1)
	{
		if ((a[leftChild] > a[counter]) && (a[leftChild] >= a[rightChild]))
		{
			swap(a, leftChild, counter);
			siftDown(a, leftChild, num);
		}
		else if ((a[rightChild] > a[counter]) && (a[rightChild] >= a[leftChild]))
		{
			swap(a, rightChild, counter);
			siftDown(a, rightChild, num);
		}
	}
}

void buildHeap(int a[], int num)
{
	for (int i = num / 2 - 1; i >= 0; --i)
	{
		siftDown(a, i, num);
	}
}

void heapSort(int a[], int num)
{
	buildHeap(a, num);
	int size = num;
	for (int i = num - 1; i >= 1; --i)
	{
		swap(a, i, 0);
		--size;
		siftDown(a, 0, size);
	}
}

int main()
{
	int n = 0;
	std::cin >> n;
	int* arr = new int[n];
	int value = 0;
	for (int i = 0; i < n; ++i)
	{
		std::cin >> value;
		arr[i] = value;
	}

	heapSort(arr, n);
	for (int i = 0; i < n; ++i)
	{
		std::cout << arr[i] << " ";
	}

	delete[] arr;
	return 0;
}
