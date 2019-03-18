/*
 * Factorial.cpp
 */

#include "Factorial.h"

int factorialRecurs(int n)
{
	if(n == 0)
		return 1;
	else
		return n*factorialRecurs(n-1);

}

int factorialDinam(int n)
{
	int a = 1;

	for(int i = 1; i <= n; i++)
		a *=i;

	return a;

}
