
class Conway {

public:
	Conway(Settings* settings);
	~Conway();

	/* Configuration & initialization */
	Settings* settings;
	
	bool* birthValues;
	bool* surviveValues;
	
	/* Space & mutation  */
	void run();
	Space* space;
	int turn;
	void takeTurn();
	void mutateAll();
	void mutateCell(int i);
};
