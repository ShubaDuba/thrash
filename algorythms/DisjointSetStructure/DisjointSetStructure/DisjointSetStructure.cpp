#include <iostream>
#include <string.h>

struct Node{
	Node* parent;
	int rank;
	int number;
};

Node *makeSet(int number)
{
	Node *tmp = new Node;
	tmp->number = number;
	tmp->parent = tmp;
	tmp->rank = 0;
	return tmp;
}

int setFind(int number, Node arr[])
{
	int result = number - 1;
	while (arr[result].parent->number != arr[result].number)
	{
		result = arr[result].parent->number;
	}

	return result;
}

void setUnion(int x, int y, Node arr[])
{
	int rootX = setFind(x, arr);
	int rootY = setFind(y, arr);
	if (rootX == rootY)
	{
		return;
	}

	if (arr[rootX].rank > arr[rootY].rank)
	{
		arr[rootY].parent = &arr[rootX];
	}
	else
	{
		arr[rootX].parent = &arr[rootY];
		if (arr[rootX].rank == arr[rootY].rank)
		{
			++arr[rootX].rank;
		}
	}
}

int main()
{
	int n = 0;
	std::cin >> n;
	int m = 0;
	std::cin >> m;
	Node *arr = new Node[n];
	for (int i = 0; i < n; ++i)
	{
		arr[i] = *makeSet(i);
	}

	int first = 0;
	int second = 0;
	char *tmp = new char[5];
	for (int i = 0; i < m; ++i)
	{
		std::cin >> tmp >> first >> second;
		if (strcmp(tmp, "Union") == 0)
		{
			setUnion(first, second, arr);
		}
		else if (strcmp(tmp, "Check") == 0)
		{
			if (setFind(first, arr) == setFind(second, arr))
			{
				std::cout << "True" << "\n";
			}
			else
			{
				std::cout << "False" << "\n";
			}
		}
	}

	delete[] arr;
	return 0;
}