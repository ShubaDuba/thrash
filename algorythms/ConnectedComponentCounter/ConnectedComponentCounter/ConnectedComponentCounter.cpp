#include <iostream>

struct Node
{
	Node *next;
	int number;
};

struct List
{
	Node *head;
	Node *tail;
};

Node *initNode(int number)
{
	Node *n = new Node;
	n->next = NULL;
	n->number = number;
	return n;
}

void addToList(List list[], int first, int second)
{
	Node *tmp = initNode(second);
	if (list[first].head == NULL)
	{
		list[first].head = tmp;
		list[first].tail = tmp;
	}
	else
	{
		list[first].tail->next = tmp;
		list[first].tail = tmp;
	}
}

void explore(List list[], bool visited[], int v)
{
	visited[v - 1] = true;
	Node *current = list[v - 1].head;
	while (current != NULL)
	{
		if (!visited[current->number - 1])
		{
			explore(list, visited, current->number);
		}

		current = current->next;
	}
}

int componentCount(List list[], int n)
{
	int counter = 0;
	bool *visited = new bool[n];
	for (int i = 0; i < n; ++i)
	{
		visited[i] = false;
	}

	for (int i = 0; i < n; ++i)
	{
		if (!visited[i])
		{
			explore(list, visited, i + 1);
			++counter;
		}
	}
	return counter;
}

int main()
{
	int n = 0;
	int m = 0;
	std::cin >> n >> m;
	int u = 0;
	int v = 0;
	List *nodes = new List[n];
	for (int i = 0; i < n; ++i)
	{
		nodes[i].head = NULL;
		nodes[i].tail = NULL;
	}

	for (int i = 0; i < m; ++i)
	{
		std::cin >> u >> v;
		addToList(nodes, u - 1, v);
		addToList(nodes, v - 1, u);
	}

	std::cout << componentCount(nodes, n);
	delete[] nodes;
}
