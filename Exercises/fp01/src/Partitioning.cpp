/*
 * Partioning.cpp
 */

#include "Partitioning.h"


int s_recursive(int n,int k)
{
   if((k == 1) || (k == n))
   	return 1;
   else
   	return s_recursive(n-1,k-1) + k * s_recursive(n-1,k);

}

int s_dynamic(int n,int k)
{
	int* column = (int*) malloc(sizeof(int) * n);

	int maxj = n - k ;

	for (int j = 0; j <= maxj; j++)
		column[j] = 1;

	for (int i = 2; i <= k; i++)
		for (int j = 1; j <= maxj; j++)
			column[j] += column[j-1] *  i;

	int result = column[maxj];
	free(column);

	return result;

}


int b_recursive(int n)
{
	int result = 0;

	for(size_t i = 1; i <= n; i++)
		result += s_recursive(n,i);

	return result;
}

int b_dynamic(int n)
{
	int* row = (int*) malloc(sizeof(int) * n);


	for (int i = 1; i <= n; i++){

		row[i-1] = 1;

		for (int j = i -1 ; j > 1; j--)
			row[j] = row[j-1] + row[j] *  j;
	}


	int result = 0;

	for(int i = 0; i < n; i++)
		result += row[i];

	return result;


}


