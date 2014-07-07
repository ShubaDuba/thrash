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

void explore(List list[], bool visited[], int begins[], int ends[], int v, int *time, bool *weFoundCycle)
{
	visited[v - 1] = true;
	Node *current = list[v - 1].head;
	while (current != NULL)
	{
		if (!visited[current->number - 1])
		{
			begins[current->number - 1] = (*time)++;
			explore(list, visited, begins, ends, current->number, time, weFoundCycle);
			ends[current->number - 1] = (*time)++;
		}
		else
		{
			if ((*time > begins[current->number - 1]) && (ends[current->number - 1] == -1))
			{
				*weFoundCycle = true;
			}
		}

		current = current->next;
	}
}

bool cycleIsFound(List list[], int n)
{
	int time = 0;
	int *begins = new int[n];
	int *ends = new int[n];
	for (int i = 0; i < n; ++i)
	{
		begins[i] = -1;
		ends[i] = -1;
	}

	bool weFoundCycle = false;
	bool *visited = new bool[n];
	for (int i = 0; i < n; ++i)
	{
		visited[i] = false;
	}

	for (int i = 0; i < n; ++i)
	{
		if (!visited[i])
		{
			begins[i] = time++;
			explore(list, visited, begins, ends, i + 1, &time, &weFoundCycle);
			ends[i] = time++;
		}
	}

	delete[] begins;
	delete[] ends;
	return weFoundCycle;
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
	}

	if (cycleIsFound(nodes, n))
	{
		std::cout << "True";
	}
	else
	{
		std::cout << "False";
	}

	delete[] nodes;
}