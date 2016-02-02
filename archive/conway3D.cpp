#include "shared.h"

conway3D::conway3D(int activateMinimum, int activateMaximum, int surviveMinimum, int surviveMaximum, int size, bool wrap)
	: ca3Dbase(size, wrap)

{
	this->activateMinimum = activateMinimum;
	this->activateMaximum = activateMaximum;
	this->surviveMinimum = surviveMinimum;
	this->surviveMaximum = surviveMaximum;
}

void conway3D::mutatebyindex(int i)
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

	space->setCell(i, newAlive);
}
