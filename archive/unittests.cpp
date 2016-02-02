#include "shared.h"

void unittests::assert(bool expression, const char* errorMessage)
{
	if (!expression) {
		throw new exception(errorMessage);
	}
}

void unittests::runalltests()
{
	testspace3D();
}

void unittests::testspace3D()
{
	int extents[3] {3, 3, 3};
	space* space = new space(3, extents, false);


	int ordinates[3] {1, 1, 1};
	int index = space->getIndex(ordinates, space->isSwapped);
	int* adj = space->cellAdjacencies[index];
	for (int i = 0; i < 26; i++)
	{
		int zz = adj[i];
	}

	space->swap();

	index = space->getIndex(ordinates, space->isSwapped);
	adj = space->cellAdjacencies[index];
	for (int i = 0; i < 26; i++)
	{
		int zz = adj[i];
	}

	delete space;
}