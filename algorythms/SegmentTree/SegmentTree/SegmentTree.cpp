#include <iostream>
#include <string.h>
#include <math.h>

const int inf = 2147483647;
void treeInit(int a[], int segmentTree[], int n, int treeSize, int lastRowSize)
{
	int flag = 0;
	for (int i = treeSize - lastRowSize; i < treeSize - lastRowSize + n; ++i)
	{
		segmentTree[i] = a[flag++];
	}

	for (int i = treeSize - lastRowSize + n; i < treeSize; ++i)
	{
		segmentTree[i] = inf;
	}

	for (int i = treeSize - lastRowSize - 1; i >= 0; --i)
	{
		if (segmentTree[i * 2 + 1] < segmentTree[i * 2 + 2])
		{
			segmentTree[i] = segmentTree[i * 2 + 1];
		}
		else
		{
			segmentTree[i] = segmentTree[i * 2 + 2];
		}
	}
}

int getMin(int a[], int element, int left, int right, int leftBorder, int rightBorder)
{
	if ((left == leftBorder) && (right == rightBorder))
	{
		return a[element];
	}

	int midBorder = (leftBorder + rightBorder) / 2;
	if ((left <= midBorder) && (right > midBorder))
	{
		int leftChild = getMin(a, element * 2 + 1, left, midBorder, leftBorder, midBorder);
		int rightChild = getMin(a, element * 2 + 2, midBorder + 1, right, midBorder + 1, rightBorder);
		if (leftChild > rightChild)
		{
			return rightChild;
		}
		else
		{
			return leftChild;
		}
	}
	else if (left > midBorder)
	{
		return getMin(a, element * 2 + 2, left, right, midBorder + 1, rightBorder);
	}
	else if (right < midBorder + 1)
	{
		return getMin(a, element * 2 + 1, left, right, leftBorder, midBorder);
	}

	return 0;
}

void setValue(int a[], int tree[], int num, int value, int treeSize, int lastRowSize)
{
	a[num - 1] = value;
	int flag = treeSize - lastRowSize + num - 1;
	tree[flag] = value;
	int parent = 0;
	int leftChild = 0;
	int rightChild = 0;
	while (flag != 0)
	{
		parent = (flag - 1) / 2;
		leftChild = 2 * parent + 1;
		rightChild = 2 * parent + 2;
		if (tree[leftChild] < tree[rightChild])
		{
			tree[parent] = tree[leftChild];
		}
		else
		{
			tree[parent] = tree[rightChild];
		}

		flag = parent;
	}
}

int main()
{
	int n = 0;
	std::cin >> n;
	int m = 0;
	std::cin >> m;
	int *arr = new int[n];
	for (int i = 0; i < n; ++i)
	{
		std::cin >> arr[i];
	}

	int lastRowSize = 1;
	while (lastRowSize < n)
	{
		lastRowSize *= 2;
	}

	int treeSize = 2 * lastRowSize - 1;
	int *tree = new int[treeSize];
	treeInit(arr, tree, n, treeSize, lastRowSize);
	char *tmp = new char[3];
	int counter = 0;
	int num = 0;
	int value = 0;
	int left = 0;
	int right = 0;
	for (int i = 0; i < m; ++i)
	{
		std::cin >> tmp;
		if (strcmp(tmp, "Min") == 0)
		{
			std::cin >> left >> right;
			std::cout << getMin(tree, 0, left, right, 1, lastRowSize) << "\n";
		}
		else if (strcmp(tmp, "Set") == 0)
		{
			std::cin >> num >> value;
			setValue(arr, tree, num, value, treeSize, lastRowSize);
		}
	}

	delete[] arr;
	delete[] tree;
	return 0;
}
