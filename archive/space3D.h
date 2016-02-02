


class space3D
{
public:

	space3D(int size, bool wrap = true);

	~space3D();
	
	int matSize;

	unsigned char* mat;

	int size;

	bool wrap;

	bool swapped;

	void swap();

	inline int getindex(int x, int y, int z, bool useswapped);

	inline int getindex_unchecked(int x, int y, int z, bool useswapped);

	// Gets from current matrix
	unsigned char getelem(int x, int y, int z);

	// Sets in swapped matrix
	void setelem(int x, int y, int z, unsigned char state);

	float calculateAliveAmount();

	float calculateChangeAmount();

	bool isDead();

	bool isClogged();

	void cacheAdjacencies();

	int** adjacencies;    
	
	int* getAdjacencies(int i, bool useSwapped);

	int getIndex(int i, bool useSwapped);

	int nullCellIndex;
};

