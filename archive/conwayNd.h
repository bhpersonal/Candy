#include "shared.h"

class conwayNd : public conway
{
public:
	conwayNd(int activateMinimum, int activateMaximum, int surviveMinimum, int surviveMaximum, int size = 50, bool wrap = true, int depth = 5);

	int activateMinimum, activateMaximum, surviveMinimum, surviveMaximum;

	void mutatebyindex(int i);
};