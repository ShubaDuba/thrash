//curve addiction, but it works!
#pragma once
#include <stdio.h>
#include <iostream>

struct StackElement
{
	unsigned long long int value;
	StackElement* next;
};

struct Stack
{
	StackElement* head;
};

typedef StackElement* Position;

Stack* createStack()
{
	Stack* tmp = new Stack;
	tmp->head = NULL;
	return tmp;
}

void addElement(Stack* stack, unsigned long long int value)
{
	Position tmp = stack->head;
	StackElement* element = new StackElement;
	element->next = NULL;
	element->value = value;

	if (tmp == NULL)
	{
		stack->head = element;
		return;
	}

	while(tmp->next != NULL)
	{
		tmp = tmp->next;
	}

	tmp->next = element;
}

void deleteStack(Stack* stack)
{
	if (stack->head == NULL)
		return;

	if (stack->head->next == NULL)
	{
		delete stack->head;
		return;
	}

	Position element = stack->head;
	while (element->next != NULL)
	{
		Position tmp = element;
		element = element->next;
		delete tmp;
	}
}

void matrixMultiplyMod (unsigned long long int* m1[], unsigned long long int* m2[], unsigned long long int mod)
{
	unsigned long long int** result = new unsigned long long int*[2];
	for (int i = 0; i < 2; ++i)
	{
		result[i] = new unsigned long long int[2];
	}

	result[0][0] = (m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0]) % mod;
	result[0][1] = (m1[0][0] * m2[0][1] + m1[0][1] * m2[1][1]) % mod;
	result[1][0] = (m1[1][0] * m2[0][0] + m1[1][1] * m2[1][0]) % mod;
	result[1][1] = (m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1]) % mod;
	m1[0][0] = result[0][0];
	m1[0][1] = result[0][1];
	m1[1][0] = result[1][0];
	m1[1][1] = result[1][1];
	for (int i = 0; i < 2; i++)
	{
		delete[] result[i];
	}

	delete[] result;
}

void matrixPowerMod (unsigned long long int* m1[], unsigned long long int power, unsigned long long int mod)
{
	for (unsigned long long int i = 0; i <= power; ++i) 
	{
		matrixMultiplyMod (m1, m1, mod);
	}
}

unsigned long long int fibmod(unsigned long long int n, unsigned long long int mod)
{
	if (n <= 1)
	{
		return 1;
	}

	Stack *powers = createStack();
	unsigned long long int flag = 0;
	unsigned long long int stackSize = 0;
	while (n >= 1)
	{
		if (n % 2 == 1)
		{
			addElement(powers, flag);
			++stackSize;
		}

		++flag;
		n /= 2;
	}

	unsigned long long int **result = new unsigned long long int*[2];
	unsigned long long int **tmp1 = new unsigned long long int*[2];
	unsigned long long int **tmp2 = new unsigned long long int*[2];
	for (int i = 0; i < 2; ++i)
	{
		result[i] = new unsigned long long int[2];
		tmp1[i] = new unsigned long long int[2];
		tmp2[i] = new unsigned long long int[2];
	}

	tmp1[0][0] = 1;
	tmp1[1][0] = 0;
	tmp1[0][1] = 0;
	tmp1[1][1] = 1;
	tmp2[0][0] = 1;
	tmp2[1][0] = 1;
	tmp2[0][1] = 1;
	tmp2[1][1] = 0;
	Position iter = powers->head;
	for (unsigned long long int i = 0; i < stackSize; ++i)
	{
		for (unsigned long long int j = 0; j < iter->value; ++j) 
		{
			result[0][0] = (tmp2[0][0] * tmp2[0][0] + tmp2[0][1] * tmp2[1][0]) % mod;
			result[0][1] = (tmp2[0][0] * tmp2[0][1] + tmp2[0][1] * tmp2[1][1]) % mod;
			result[1][0] = (tmp2[1][0] * tmp2[0][0] + tmp2[1][1] * tmp2[1][0]) % mod;
			result[1][1] = (tmp2[1][0] * tmp2[0][1] + tmp2[1][1] * tmp2[1][1]) % mod;
			tmp2[0][0] = result[0][0];
			tmp2[0][1] = result[0][1];
			tmp2[1][0] = result[1][0];
			tmp2[1][1] = result[1][1];
		}

		result[0][0] = (tmp1[0][0] * tmp2[0][0] + tmp1[0][1] * tmp2[1][0]) % mod;
		result[0][1] = (tmp1[0][0] * tmp2[0][1] + tmp1[0][1] * tmp2[1][1]) % mod;
		result[1][0] = (tmp1[1][0] * tmp2[0][0] + tmp1[1][1] * tmp2[1][0]) % mod;
		result[1][1] = (tmp1[1][0] * tmp2[0][1] + tmp1[1][1] * tmp2[1][1]) % mod;
		tmp1[0][0] = result[0][0];
		tmp1[0][1] = result[0][1];
		tmp1[1][0] = result[1][0];
		tmp1[1][1] = result[1][1];
		iter = iter->next;
		tmp2[0][0] = 1;
		tmp2[1][0] = 1;
		tmp2[0][1] = 1;
		tmp2[1][1] = 0;
	}

	unsigned long long int answer = tmp1[0][1];
	for (int i = 0; i < 2; i++)
	{
		delete[] result[i];
	}
	
	delete[] result;

	deleteStack(powers);
	for (int i = 0; i < 2; i++)
	{
		delete[] tmp1[i];
		delete[] tmp2[i];
	}

	delete[] tmp1;
	delete[] tmp2;
	return answer;
}

int main() {	
	unsigned long long int num;
	std::cin >> num;
	unsigned long long int mod;
	std::cin >> mod;
	std::cout << fibmod(num, mod);
	return 0;
}