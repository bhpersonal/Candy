#include "shared.h"

class conway4D : public ca4Dbase
{
public:
	conway4D(int activateMinimum, int activateMaximum, int surviveMinimum, int surviveMaximum, int size = 50, bool wrap = true, int depth = 20);

	int activateMinimum, activateMaximum, surviveMinimum, surviveMaximum;

	void mutatebyindex(int i);
};
