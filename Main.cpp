/*
 * David Zuccaro and Brendan Hill
 * Copyright 2014 */


#include "shared.h"

int main(int argc, char **argv)
{
	Settings* settings = new Settings(argc, argv);
	Conway* conway = new Conway(settings);

	if (settings->renderMethod == NoRender)
	{
		conway->run();
	}
	else
	{
		Renderer* renderer = new Renderer(conway);
		renderer->run();
	}
	
	return 0;
}
