#include "Shared.h"

void Seeds::Create(Space* space, SeedShape seedShape)
{
	// TODO



	// TODO - cleanup & seed options

	int middle = (int)(space->extents[0] / 2);
	//float middleF = size / 2;
	//float maxDistance = sqrt(pow(middleF, 2) + pow(middleF, 2) + pow(middleF, 2));

	unsigned char toggle = 0;
	//int toggle = 0;
	// TODO n-dimension
	int ordinates[9];

	//float middleF = size / 2;
	//float maxDistance = sqrt(pow(middleF, 2) + pow(middleF, 2) + pow(middleF, 2));

	for (int x = middle - 1; x <= middle + 1; x++)
		for (int y = middle - 1; y <= middle + 1; y++)
			for (int z = middle - 1; z <= middle + 1; z++)
				for (int w = 1; w <= 3; w++)
				{
					ordinates[0] = x;
					ordinates[1] = y;
					ordinates[2] = z;
					ordinates[3] = w;
					ordinates[4] = w;
					ordinates[5] = w;
					//ordinates[6] = w;

					bool coinFlip = ((double)rand() / RAND_MAX) > .8f;
					unsigned char isAlive = coinFlip ? 1 : 0;
					space->setCell(ordinates, isAlive);

					//space->setCell(ordinates, 1);
				}

	space->swap();
}