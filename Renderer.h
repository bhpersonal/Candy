#include "Shared.h"

class Renderer
{
public:
	Renderer(Conway* conway);
	~Renderer();

	void run();

	Space* space;
	Settings* settings;
	Conway* conway;

	/* Initialization */
	void initializeGlut();
	void initializeGraphics();
	void initializeCamera();
	void initializePixels();
	
	Color* pixelColors;
	Vector3d* pixelVectors;

	/* Running */
	void takeTurn();

	/* Rendering */
	Cursor* cursor;
	void reshape(int w, int h);
	void render();
	void drawString(void * font, char *s, float x, float y, float z);

	/* Camera control */
	bool moveright, moveup, movefor;
	double xvel, yvel, zvel;
	double xang, yang, zang;
	double xloc, yloc, zloc;
	double zpos;
	void keyboard(unsigned char key, int x, int y);
};


class RendererGlobal
{
public:
	static Renderer* CurrentRenderer;

	static void taketurn()
	{
		CurrentRenderer->takeTurn();
	}

	static void reshape(int w, int h)
	{
		CurrentRenderer->reshape(w, h);
	}

	static void keyboard(unsigned char key, int x, int y)
	{
		CurrentRenderer->keyboard(key, x, y);
	}
};         