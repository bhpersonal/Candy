#include "shared.h"

conwayNd::conwayNd(int activateMinimum, int activateMaximum, int surviveMinimum, int surviveMaximum, int size, bool wrap, int depth)
	: conway(size, wrap, depth)

{
	this->activateMinimum = activateMinimum;
	this->activateMaximum = activateMaximum;
	this->surviveMinimum = surviveMinimum;
	this->surviveMaximum = surviveMaximum;
}

void conwayNd::mutatebyindex(int i)
{
	//int currentindex = space->getIndex(i, space->isSwapped);
	unsigned char oldAlive = space->getCell(i);
	int neighbours = space->countLiveAdjacencies(i);

	unsigned char newAlive;
	if (oldAlive == 0)
	{
		newAlive = (unsigned char)(int)(neighbours >= activateMinimum && neighbours <= activateMaximum);
	}
	else
	{
		newAlive = (unsigned char)(int)(neighbours >= surviveMinimum && neighbours <= surviveMaximum);
	}

	if (newAlive == 1)
	{
		int iii = 1;
	}

	space->setCell(i, newAlive);
}
