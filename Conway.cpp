#include "shared.h"

Conway::Conway(Settings* settings)
{
	this->settings = settings;

	space = new Space(settings->dims, settings->size, settings->wrap);

	Seeds::Create(space, settings->seedShape);
	
	birthValues = new bool[space->adjacenciesPerCellCount + 1];
	memset(birthValues, 0, space->adjacenciesPerCellCount + 1);
	for (int i = 0; i < settings->birthCount; i++)
	{
		birthValues[settings->birth[i]] = true;
	}

	surviveValues = new bool[space->adjacenciesPerCellCount + 1];
	memset(surviveValues, 0, space->adjacenciesPerCellCount + 1);
	for (int i = 0; i < settings->surviveCount; i++)
	{
		surviveValues[settings->survive[i]] = true;
	}

	if (settings->outputFile.length() > 0) {
		std::ofstream log(settings->outputFile, std::ios_base::out);
		log << "Turn,AlivePercentage,ChangePercentage\n";
		log.close();
	}
}

Conway::~Conway()
{
	delete surviveValues;
	delete birthValues;
	delete space;
}

void Conway::run()
{
	for (turn = 0; turn < settings->turns; turn++)
	{
		takeTurn();
	}
}
void Conway::takeTurn()
{
	mutateAll();
	space->swap();
	turn++;

	// TODO: Write to output file
	if (settings->outputFile.length() > 0) {
		std::ofstream log(settings->outputFile, std::ios_base::app | std::ios_base::out);
		log << turn << "," << space->calculateAlivePercent() << "," << space->calculateChangePercent() << "\n";
		log.close();
	}
}

void Conway::mutateAll()
{
	for (int i = 0; i < space->matrixSize; i++)
	{
		mutateCell(i);
	}
}

void Conway::mutateCell(int i)
{
	int neighbours = space->countLiveAdjacencies(i);

	
	if (!space->getCell(i))
	{
		space->setCell(i, birthValues[neighbours]);
	}
	else
	{
		space->setCell(i, surviveValues[neighbours]);
	}

	//space->setCell(i, !space->getCell(i));
	
	if (neighbours > 0)
		cout << neighbours << "\n";
}
