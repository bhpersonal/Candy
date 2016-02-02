#include "Shared.h"

enum RenderMethods
{
	NoRender,
	RenderMethodMiddleSlice,    // Can render N dimensions
	RenderMethodExplodeHigherDimensions,   // Can render N dimensions
	RenderMethodMaxIntensity,   // Can render 6 dimensions
};

enum PixelShapes
{
	PixelShapeCube,
	PixelShapeSphere,
};

enum SeedShape
{
	NoSeed,
	SeedShapeBox,
	SeedShapeLines,
	SeedShapeAlternating,
	SeedShapeRandom,
	SeedShapeRandomNearCentre,
};

class Settings
{
public:
	Settings();
	Settings(int argc, char **argv);
	~Settings();

	//   dims=X
	int dims;

	//   size=X,Y,Z,W...
	int* size;

	//    wrap
	bool wrap;

	//    birth=1,2,5,6
	int* birth;

	int birthCount;

	//    survive=1,2,3,4
	int* survive;

	int surviveCount;

	//    turns=X
	int turns;

	//    outputfile="C:\...."
	std::string outputFile;

	//    renderMethod=None/MiddleSlice etc
	RenderMethods renderMethod;

	//    pixelShape=Cube
	PixelShapes pixelShape;

	//    seedShape=....
	SeedShape seedShape;

	//    seedValue=X
	float seedValue; // size, random weighting, etc
};



