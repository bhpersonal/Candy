#include "shared.h"

int* CsvToIntArray(std::string csv)
{
	int* rv = new int[csv.size()];

	vector<string> strs = split(csv, ',');

	for (int i = 0; i < strs.size(); i++)
	{
		rv[i] = atoi(strs.at(i).c_str());
	}

	return rv;
}

Settings::Settings()
{
	dims = 2;
	size = new int[3] { 50, 50 };
	wrap = false;

	birth = new int[2] { 3, 5};
	birthCount = 2;

	survive = new int[1] { 4 };
	surviveCount = 1;

	turns = 1000000;
	outputFile = "";
	renderMethod = RenderMethodMiddleSlice;
	pixelShape = PixelShapeCube;
	seedShape = SeedShapeBox;
	seedValue = 2;
}


Settings::Settings(int argc, char **argv) : Settings()
{
	for (int i = 1; i < argc; i++)
	{
		string arg(argv[i]);

		size_t eqPos = arg.find('=');

		std::string param;
		std::string value;

		if (eqPos != string::npos)
		{
			param = arg.substr(0, eqPos);
			value = arg.substr(eqPos + 1, arg.length() - eqPos - 1);
		}
		else
		{
			param = arg;
		}

		std::transform(param.begin(), param.end(), param.begin(), ::tolower);

		if (param.compare("dims") == 0)
		{
			dims = atoi(value.c_str());
			size = new int[dims];
		}
		else if (param.compare("size") == 0)
		{
			vector<string> values = split(value, ',');

			delete size;
			size = new int[dims];

			if (values.size() == 1)
			{
				int s = atoi(values.at(0).c_str());
				for (int i = 0; i < dims; i++)
				{
					size[i] = s;
				}
			}
			else if (values.size() == dims)
			{
				for (int i = 0; i < dims; i++)
				{
					size[i] = atoi(values.at(i).c_str());
				}
			}
			else
			{
				string message = "Invalid size parameter - must be a single value, or same number as dims.";
				cout << message;
				throw exception(message.c_str());
			}

		}
		else if (param.compare("wrap") == 0)
		{
			wrap = true;
		}
		else if (param.compare("birth") == 0)
		{
			delete birth;
			birth = CsvToIntArray(value);
			birthCount = split(value, ',').size();
		}
		else if (param.compare("survive") == 0)
		{
			delete survive;
			survive = CsvToIntArray(value);
			surviveCount = split(value, ',').size();
		}
		else if (param.compare("turns") == 0)
		{
			turns = atoi(value.c_str());
		}
		else if (param.compare("file") == 0)
		{
			outputFile = value;
		}
		else if (param.compare("render") == 0)
		{
			std::transform(value.begin(), value.end(), value.begin(), ::tolower);

			if (value.compare("slice") == 0)
			{
				renderMethod = RenderMethodMiddleSlice;
			}
			else if (value.compare("explode") == 0)
			{
				renderMethod = RenderMethodExplodeHigherDimensions;
			}
			else if (value.compare("intensity") == 0)
			{
				renderMethod = RenderMethodMaxIntensity;
			}
			else 
			{
				string message = "Unknown render parameter";
				cout << message;
				cout << value;
				throw exception(message.c_str());
			}
		}
		else if (param.compare("pixelshape") == 0)
		{
			std::transform(value.begin(), value.end(), value.begin(), ::tolower);

			if (value.compare("cube") == 0)
			{
				pixelShape = PixelShapeCube;
			} 
			else if (value.compare("sphere") == 0)
			{
				pixelShape = PixelShapeSphere;
			}
			else
			{
				string message = "Unknown pixel shape parameter";
				cout << message;
				cout << value;
				throw exception(message.c_str());
			}

		}
		else if (param.compare("seedshape") == 0)
		{
			std::transform(value.begin(), value.end(), value.begin(), ::tolower);

			if (value.compare("cube") == 0)
			{
				seedShape = SeedShapeBox;
			}
			else if (value.compare("lines") == 0)
			{
				seedShape = SeedShapeLines;
			}
			else if (value.compare("alternating") == 0)
			{
				seedShape = SeedShapeAlternating;
			}
			else if (value.compare("random") == 0)
			{
				seedShape = SeedShapeRandom;
			}
			else if (value.compare("randomcentre") == 0)
			{
				seedShape = SeedShapeRandomNearCentre;
			}
			else
			{
				string message = "Unknown seed shape parameter";
				cout << message;
				cout << value;
				throw exception(message.c_str());
			}
		}
		else if (param.compare("seedvalue") == 0)
		{
			seedValue = atof(value.c_str());
		}
		else
		{
			string message = "Unknown command line parameter: " + param;
			cout << message;
			throw exception(message.c_str());
		}
	}
}

Settings::~Settings()
{	
	delete size;
	delete birth;
	delete survive;
}
