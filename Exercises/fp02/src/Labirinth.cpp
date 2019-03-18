/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>
using namespace std;



Labirinth::Labirinth(int values[10][10])
{
	initializeVisited();

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			labirinth[i][j] = values[i][j];
}


void Labirinth::initializeVisited()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			visited[i][j] = false;
}




void  Labirinth::printLabirinth()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << labirinth[i][j] << " ";

		cout << endl;
	}
}


bool Labirinth::findGoal(int x, int y)
{

	if ( (x < 0) || (y < 0) || (x > 9) || (y > 9))
		return false;
	else if(labirinth[x][y] == 2)
		return true;
	else if(labirinth[x][y]  == 0)
		return false;
	else if(visited[x][y])
		return false;
	else{
		visited[x][y] = true;

		if(findGoal(x+1 , y))
			return true;
		if(findGoal(x-1,y))
			return true;
		if(findGoal(x,y+1))
			return true;
		if(findGoal(x,y-1))
			return true;
	}

	return false;
}


