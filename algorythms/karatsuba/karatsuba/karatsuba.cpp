#include <iostream>
#include <string>
#include <stdio.h>

const int BASE = 10;
const int LENGTH_FOR_SIMPLE_MULT = 50;

using namespace std;

struct longNumber{
	int *digits;
	int length;
};

void fixLength(longNumber &num)
{
	while ((num.digits[num.length - 1] == 0) && (num.length > 0))
	{
		--num.length;
	}
}

longNumber sum(longNumber first, longNumber second)
{
	longNumber sum;
	sum.digits = new int[first.length + 1];
	sum.length = first.length + 1;
	sum.digits[sum.length - 1] = 0;
	int buffer = 0;

	for (int i = 0; i < second.length; ++i)	//first number must be longer than second
	{
		sum.digits[i] = first.digits[i] + second.digits[i] + buffer;
		buffer = sum.digits[i] / BASE;
		sum.digits[i] = sum.digits[i] % BASE;
	}
	
	for (int i = second.length; i < first.length; ++i)
	{
		sum.digits[i] = first.digits[i] + buffer;
		buffer = sum.digits[i] / BASE;
		sum.digits[i] = sum.digits[i] % BASE;
	}

	sum.digits[first.length] = buffer;

	if (sum.digits[sum.length - 1] == 0)
	{
		--sum.length;
	}

	return sum;
}	

longNumber &sub(longNumber &first, longNumber second)
{
	int buffer = 0;
	for (int i = 0; i < second.length; ++i)
	{
		first.digits[i] -= second.digits[i] + buffer;
		if (first.digits[i] < 0)
		{
			first.digits[i] = BASE + first.digits[i];
			buffer = 1;
		}
		else
		{
			buffer = 0;
		}
	}

	if (first.length != second.length)
	{
		first.digits[second.length] -= buffer;
	}

	fixLength(first);

	return first;
}

longNumber mult(longNumber first, longNumber second)
{
	longNumber mult;
	mult.length = first.length + second.length;
	mult.digits = new int[mult.length];
	memset(mult.digits, 0, sizeof(int) * mult.length);
	int buffer = 0;
	for (int i = 0; i < first.length; ++i)
	{
		for (int j = 0; j < second.length; ++j)
		{
			int tmp = i + j;
			mult.digits[tmp] += first.digits[i] * second.digits[j] + buffer;
			buffer = mult.digits[tmp] / BASE;
			mult.digits[tmp] = mult.digits[tmp] % BASE;
		}
		
		mult.digits[i + second.length] += buffer;
		buffer = 0;
	}
	
	fixLength(mult);

	return mult;
}

longNumber karatsuba(longNumber first, longNumber second)
{
	int n = std::max(first.length, second.length);
	int m = (n + 1) / 2;
	if (n < LENGTH_FOR_SIMPLE_MULT)
	{
		return mult(first, second);
	}
	
	longNumber result;
	result.length = first.length + second.length;
	result.digits = new int[result.length];
	memset(result.digits, 0, result.length * sizeof(int));

	longNumber firstLeft;
	firstLeft.digits = first.digits;
	firstLeft.length = std::min(m, first.length);
	longNumber firstRight;
	firstRight.digits = first.digits + firstLeft.length;
	if (first.length == firstLeft.length)
	{
		firstRight.length = 0;
		firstRight.digits[0] = 0;
	}
	else
	{
		firstRight.length = first.length - m;
	}

	longNumber secondLeft;
	secondLeft.digits = second.digits;
	secondLeft.length = std::min(m, second.length);
	longNumber secondRight;
	secondRight.digits = second.digits + secondLeft.length;
	if (second.length == secondLeft.length)
	{
		secondRight.length = 0;
		secondRight.digits[0] = 0;
	}
	else
	{
		secondRight.length = second.length - m;
	}
	
	longNumber sumFirst = sum(firstLeft, firstRight);
	longNumber sumSecond = sum(secondLeft, secondRight);

	longNumber multFSsums = karatsuba(sumFirst, sumSecond);
	longNumber multLeft = karatsuba(firstLeft, secondLeft);
	longNumber multRight = karatsuba(firstRight, secondRight);
	longNumber sumMiddle = sub(sub(multFSsums, multLeft), multRight);

	memcpy(result.digits, multLeft.digits, multLeft.length * sizeof(int));
	memcpy(result.digits + m * 2, multRight.digits, multRight.length * sizeof(int));
	for (int i = 0; i < sumMiddle.length; ++i)
	{
		result.digits[m + i] += sumMiddle.digits[i];
	}

	for (int i = 0; i < result.length - 1; ++i)
	{
		if (result.digits[i] >= BASE)
		{
			int buffer = result.digits[i] / BASE;
			result.digits[i + 1] += buffer;
			result.digits[i] -= buffer * BASE;
		}
		else if (result.digits[i] < 0)
		{
			int buffer = (result.digits[i] + 1) / BASE - 1;
			result.digits[i + 1] += buffer;
			result.digits[i] -= buffer * BASE;
		}
	}
	
	fixLength(result);

	delete[] sumFirst.digits;
	delete[] sumSecond.digits;
	delete[] multFSsums.digits;
	delete[] multLeft.digits;
	delete[] multRight.digits;
	return result;
}

int main()
{
	string x = "";
	string y = "";
	getline(cin, x);
	getline(cin, y);
	longNumber first;
	first.length = x.length();
	first.digits = new int[first.length];
	int flag = 0;
	for (int i = x.length() - 1; i >= 0; --i)
	{
		first.digits[flag++] = x[i] - 48;
	}

	longNumber second;
	second.length = y.length();
	second.digits = new int[second.length];
	flag = 0;
	for (int i = y.length() - 1; i >= 0; --i)
	{
		second.digits[flag++] = y[i] - 48;
	}

	longNumber c = karatsuba(first, second);
	for (int i = c.length - 1; i >= 0; --i)
	{
		cout << c.digits[i];
	}

	scanf_s("%*s");
	return 0;
}