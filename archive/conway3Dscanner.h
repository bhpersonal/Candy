#include "shared.h"

struct rangeInt
{
public:
	rangeInt(int min, int max)
	{
		this->min = min;
		this->max = max;
	}

	int min;

	int max;
};

class conway3Dscanner {
public:

	void scan(char* folderPath, rangeInt* minimumActivateRange, rangeInt* maximumActivateRange, rangeInt* minimumKillRange, rangeInt* maximumKillRange, int turns);
};