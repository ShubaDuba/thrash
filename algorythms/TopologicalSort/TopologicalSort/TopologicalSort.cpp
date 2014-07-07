#include <iostream>

struct Node
{
	Node *next;
	int number;
};

struct Queue
{
	Node *head;
};

struct List
{
	Node *head;
	Node *tail;
};

void printQueue(Queue *q)
{
	Node *current = q->head;
	while (current != NULL)
	{
		std::cout << current->number << ' ';
		current = current->next;
	}
}

Queue *initQueue()
{
	Queue *q = new Queue;
	q->head = NULL;
	return q;
}

Node *initNode(int number)
{
	Node *n = new Node;
	n->next = NULL;
	n->number = number;
	return n;
}

void addToQueue(Queue *list, Node *node)
{
	if (list->head == NULL)
	{
		list->head = node;
	}
	else
	{
		node->next = list->head;
		list->head = node;
	}
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

void explore(List list[], bool visited[], int begins[], int ends[], int v, int *time, Queue* tsq)
{
	visited[v - 1] = true;
	Node *current = list[v - 1].head;
	while (current != NULL)
	{
		if (!visited[current->number - 1])
		{
			begins[current->number - 1] = (*time)++;
			explore(list, visited, begins, ends, current->number, time, tsq);
			ends[current->number - 1] = (*time)++;
			addToQueue(tsq, initNode(current->number));
		}

		current = current->next;
	}
}

void topologicalSortOutput(List list[], int n)
{
	Queue *tsq = initQueue();
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
			explore(list, visited, begins, ends, i + 1, &time, tsq);
			ends[i] = time++;
			addToQueue(tsq, initNode(i + 1));
		}

	}

	printQueue(tsq);
	delete[] begins;
	delete[] ends;
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

	topologicalSortOutput(nodes, n);

	delete[] nodes;
}