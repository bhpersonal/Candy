#include "shared.h"

void conway3Dscanner::scan(char* folderPath, rangeInt* minimumActivateRange, rangeInt* maximumActivateRange, rangeInt* minimumKillRange, rangeInt* maximumKillRange, int turns)
{
	//ofstream summaryFile;

	//summaryFile.open("C:\\temp\\casummary\\summary.txt");


	//for (int minimumActivate = minimumActivateRange->min; minimumActivate <= minimumActivateRange->max; minimumActivate++)
	//for (int maximumActivate = maximumActivateRange->min; maximumActivate <= maximumActivateRange->max; maximumActivate++)
	//for (int minimumKill = minimumKillRange->min; minimumKill <= minimumKillRange->max; minimumKill++)
	//for (int maximumKill = maximumKillRange->min; maximumKill <= maximumKillRange->max; maximumKill++)
	//{
		//stringstream ss;
		//ss << "C:\\temp\\casummary\\conway3d " << minimumActivate << "." << maximumActivate << "." << minimumKill << "." << maximumKill << "." << turns << " iteration.txt";

		//ofstream iterationFile;
		//iterationFile.open(ss.str());
		//ss.clear();

		//ca3Dbase* ca = new conway3D(minimumActivate, maximumActivate, minimumKill, maximumKill, 50, false);
		//ca->start();
		//int turn = 0;
		//for (turn = 0; turn < turns; turn++)
		//{
			//ca->mutateall();
			//ca->space->swap();

			//iterationFile << turn << ", " << (ca->space->calculateAlivePercent()) << ", " << (ca->space->calculateChangePercent()) << "\n";

			//if (ca->space->isDead()) break;
			//if (ca->space->isFilled()) break;
		//}

		//summaryFile << minimumActivate << "," << maximumActivate << "," << minimumKill << "," << maximumKill << "," << turn << ", " << (ca->space->calculateAlivePercent()) << ", " << (ca->space->calculateChangePercent()) << "\n";

		//delete ca;

	//}

	//summaryFile.close();
}
