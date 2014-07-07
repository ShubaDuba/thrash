#include <iostream>

const int INF = -1;

struct Node
{
	Node *next;
	int value;
};

struct Queue
{
	Node *tail;
};

struct List
{
	Node *head;
	Node *tail;
};

Queue *initQueue()
{
	Queue *q = new Queue;
	q->tail = NULL;
	return q;
}

Node *initNode(int number)
{
	Node *n = new Node;
	n->next = NULL;
	n->value = number;
	return n;
}

void enqueue(Queue *q, int number)
{
	Node *node = initNode(number);
	if (q->tail == NULL)
	{
		q->tail = node;
		q->tail->next = q->tail;
	}
	else
	{
		node->next = q->tail->next;
		q->tail->next = node;
		q->tail = node;
	}
}

int dequeue(Queue *q)
{
	if (q->tail == NULL)
	{
		return -1;
	}

	int result = q->tail->next->value;
	if (q->tail->next == q->tail)
	{
		q->tail = NULL;
	}
	else
	{
		q->tail->next = q->tail->next->next;
	}

	return result;
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

int shortcut(List list[], int u, int v, int n)
{
	Queue *q = initQueue();
	int *dist = new int[n];
	for (int i = 0; i < n; ++i)
	{
		dist[i] = INF;
	}

	dist[u - 1] = 0;
	enqueue(q, u);
	while (q->tail != NULL)
	{
		int s = dequeue(q);
		Node *current = list[s - 1].head;
		while (current != NULL)
		{
			if (dist[current->value - 1] == INF)
			{
				enqueue(q, current->value);
				dist[current->value - 1] = dist[s - 1] + 1;
			}

			current = current->next;
		}
	}

	int result = dist[v - 1];
	delete[] dist;
	return result;
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

	std::cin >> u >> v;
	std::cout << shortcut(nodes, u, v, n);

	delete[] nodes;
	return 0;
}