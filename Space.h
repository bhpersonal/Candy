
class Space
{

public:

	int bufferSize;

	int nullCellIndex;	

	bool isWrapped;

	bool isSwapped;

	int* dimensionProducts;

	void initializeAdjacencies();

	int** cellAdjacencies;

	int adjacenciesPerCellCount;

	int* getAdjacencies(int index, bool useSwapped);

	inline int getIndex(int* ordinates, bool useSwapped, bool checkOrdinates = true);

	inline int getIndex(int index, bool useSwapped);



	Space(int dimensions, int* extents, bool wrap = true);

	~Space();

	inline int* createOrdinates(int defaultValue = 0);

	void resetOrdinates(int* ordinates, int defaultValue = 0);

	void addOrdinates(int* ordinates1, int* ordinates2, int* ordinatesSum);

	inline void iterateOverOrdinates(int* ordinates, int* minimumOrdinates, int* maximumOrdinates);

	inline bool allAreEqualTo(int* ordinates, int value);

	bool* buffer;

	int dimensions;

	int matrixSize;

	int* extents;

	void swap();

	bool getCell(int* ordinates);

	bool getCell(int index);

	void setCell(int* ordinates, bool newState);

	void setCell(int index, bool newState);

	float calculateAlivePercent();

	float calculateChangePercent();

	bool isDead();

	bool isFilled();

	int countLiveAdjacencies(int index);

	
};

