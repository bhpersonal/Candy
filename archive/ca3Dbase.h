
class ca3Dbase {

public:
	ca3Dbase(unsigned int size = 50, bool wrap = true);
	~ca3Dbase();

	int size;
	bool wrap;
	int turn;

	void initglut(int argc, char **argv);

	/* CA logic */
	void initspace(unsigned int size = 50, bool wrap = true);
	spaceNd* space;
	void taketurn();
	void mutateall();
	virtual void mutatebyindex(int i) = 0;
	//int countneighbours(int x, int y, int z);
	//int countneighbours(int i, bool useSwapped);
	int run(int argc, char **argv);
	void start();

	/* Rendering */
	cursor* mycursor;
	void initgraphics();
	void reshape(int w, int h);
	void render();
	
	/* Camera & movement */
	void initcamera();
	bool moveright, moveup, movefor;

	double xvel, yvel, zvel;
	double xang, yang, zang;
	double xloc, yloc, zloc;
	double zpos;
	void keyboard(unsigned char key, int x, int y);
};


class ca3Dglobal 
{
public:
	static ca3Dbase* CurrentCA;

	static void taketurn() 
	{
		CurrentCA->taketurn();
	}

	static void reshape(int w, int h)
	{
		CurrentCA->reshape(w, h);
	}

	static void keyboard(unsigned char key, int x, int y)
	{
		CurrentCA->keyboard(key, x, y);
	}
};