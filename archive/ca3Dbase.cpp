#include "shared.h"

ca3Dbase* ca3Dglobal::CurrentCA;

ca3Dbase::ca3Dbase(unsigned int size, bool wrap)
{
	this->size = size;
	this->wrap = wrap;
	turn = 0;
}

ca3Dbase::~ca3Dbase()
{
	delete space;
	delete mycursor;
}

void ca3Dbase::initglut(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH); //set the display to Double buffer, with depth
	glutInitWindowSize(2000, 1000); //set the window size
	glutInitWindowPosition(0, 0); //set the position of the window
	glutCreateWindow("Artificial Life"); //the caption of the window
	glutDisplayFunc(ca3Dglobal::taketurn); //use the display function to draw everything
	glutIdleFunc(ca3Dglobal::taketurn); //update any variables in display, display can be changed to anyhing, as long as you move the variables to be updated, in this case, angle++;
	glutReshapeFunc(ca3Dglobal::reshape); //reshape the window accordingly
	glutKeyboardFunc(ca3Dglobal::keyboard); //check the keyboard

}

void ca3Dbase::initspace(unsigned int size, bool wrap)
{
	int* extents = new int[3];
	extents[0] = size;
	extents[1] = size;
	extents[2] = size;
	space = new spaceNd(3,extents , wrap);

	// For now - give the middle some random live cells
	// Future development - pass in initial state as parameter
	int middle = (int)(size / 2);
	//float middleF = size / 2;
	//float maxDistance = sqrt(pow(middleF, 2) + pow(middleF, 2) + pow(middleF, 2));

	unsigned char toggle = 0;
	//int toggle = 0;

	int ordinates[3];
	for (int x = middle/2 - 8; x <= middle/2 + 8; x++)
	for (int y = middle/2 - 8; y <= middle/2 + 8; y++)
	for (int z = middle/2 - 8; z <= middle/2 + 8; z++)	
	{
		ordinates[0] = x;
		ordinates[1] = y;
		ordinates[2] = z;		

		toggle = toggle == 0 ? 1 : 0;
				
		space->setCell(ordinates, toggle);
	}
	
	for (int x = middle - 7; x <= middle + 7; x++)
	for (int y = middle - 7; y <= middle + 7; y++)
	for (int z = middle - 7; z <= middle + 7; z++)	
	{
		ordinates[0] = x;
		ordinates[1] = y;
		ordinates[2] = z;		

		toggle = toggle == 0 ? 1 : 0;
				
		space->setCell(ordinates, toggle);
	}
	
	for (int x = 3*middle/2 - 7; x <= 3*middle/2 + 7; x++)
	for (int y = 3*middle/2 - 7; y <= 3*middle/2 + 7; y++)
	for (int z = 3*middle/2 - 7; z <= 3*middle/2 + 7; z++)	
	{
		ordinates[0] = x;
		ordinates[1] = y;
		ordinates[2] = z;		

		toggle = toggle == 0 ? 1 : 0;
				
		space->setCell(ordinates, toggle);
	}


	ordinates[0] = 1;
	ordinates[1] = 1;
	ordinates[2] = 1;
	space->setCell(ordinates, 1);

	space->swap();
}

void ca3Dbase::initgraphics()
{
	yang = 0;
	zpos = space->extents[0] / 2 + 15;
	xloc = -space->extents[0] / 2;
	moveright = true;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	GLfloat blackAmbientLight[] = { 0.0, 0.0, 0.0 }; 			//set the light ambient to black
	GLfloat whiteDiffuseLight[] = { 1.0, 1.0, 1.0 }; 			//set the diffuse light to white
	glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);

	double radius(0.05);
	vector* position2 = new vector(0, 0, 0);
	vector* orient2 = new vector(1, 0, 0);
	color* blue = new color(0.0, 0.0, 1.0, 1.0);
	color* white = new color(0.0, 0.0, 0.0, 1.0);
	GLfloat* shine = new float(128.0f);
	mycursor = new cursor(blue, white, radius, position2, shine, orient2);
}

void ca3Dbase::initcamera()
{
	xang = yang = zang = 0;
	xvel = yvel = zvel = 0;

	xang = 10.0;
	yang = -10.0;
	yvel = 0.0;
	
}

void ca3Dbase::taketurn()
{
	turn++;
	xang += xvel;
	yang += yvel;
	zang += zvel;

	mutateall();
	space->swap();

	cout << turn << "," << (space->calculateAlivePercent() * 100.0) << "%, " << (space->calculateChangePercent() * 100.0) << "%\n";
	
	render();
}

void ca3Dbase::mutateall()
{
	/*int size = space->size;
	for (int x = 0; x < size; x++)
	for (int y = 0; y < size; y++)
	for (int z = 0; z < size; z++)
	{	
		mutatebycoordinates(x, y, z);
	}*/
	
	for (int i = 0; i < space->matrixSize; i++) 
	{
		mutatebyindex(i);
	}
}


void drawString(void * font, char *s, float x, float y, float z){
	unsigned int i;

	glDisable(GL_LIGHTING);
	glRasterPos3f(x, y, z);
	glColor3f(1.0, 1.0, 0.0);
	for (i = 0; i < strlen(s); i++)
		glutBitmapCharacter(font, s[i]);

	glEnable(GL_LIGHTING);
}


#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
	(std::ostringstream() << std::dec << x)).str()

void ca3Dbase::render()
{	
	color* custom;
	vector d(0, 0, 0);
	vector ep(0, 0, 0);
	
	custom = new color(0.4, 1.0, 0.2, 1.0);
	
	glClearColor(0.0, 0.0, 0.0, 1.0); 						//clear the screen to black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 	//clear the color buffer and the depth buffer

	glLoadIdentity();

	//light();
	GLfloat blackAmbientLight[] = { 0.0, 0.0, 0.0 }; 			//set the light ambient to black
	GLfloat whiteDiffuseLight[] = { 1.0, 1.0, 1.0 }; 			//set the diffuse light to white
	glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);

	gluLookAt(0, 0, zpos, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //camera position, x,y,z, looking at x,y,z, Up Positions of the camera    	    	      
	glRotatef(xang, 1.0f, 0.0f, 0.0f);
	glRotatef(yang, 0.0f, 1.0f, 0.0f);
	glRotatef(zang, 0.0f, 0.0f, 1.0f);

	int ordinates[3]; 
	for (float x = 0; x < space->extents[0]; x++)
	for (float y = 0; y < space->extents[1]; y++)
	for (float z = 0; z < space->extents[2]; z++)
	{
		ordinates[0] = x;
		ordinates[1] = y;
		ordinates[2] = z;
		unsigned char state = space->getCell(ordinates);
		if (state == 1) {


			float r = (x / space->extents[0]);// *.8 + .1;
			float g = (y / space->extents[1]);// *.8 + .1;
			float b = (z / space->extents[2]);// *.8 + .1;
			custom->rgb[0] = r;
			custom->rgb[1] = g;
			custom->rgb[2] = b;
			custom->alpha = 0.8;


			d.x = x / 10.0 - (float)space->extents[0] / 20;
			d.y = y / 10.0 - (float)space->extents[1] / 20;
			d.z = z / 10.0 - (float)space->extents[2] / 20;
			mycursor->moveabs(&d);
			mycursor->setcolor(custom);
			mycursor->pset();
		}
	}

	glRotatef(-xang, 1.0f, 0.0f, 0.0f);
	glRotatef(-yang, 0.0f, 1.0f, 0.0f);
	glRotatef(-zang, 0.0f, 0.0f, 1.0f);

	std::stringstream ss;
	ss << turn;
	string str = ss.str();
	const char* sstr = str.c_str();
	drawString(GLUT_BITMAP_HELVETICA_18, (char*)sstr, 3, 3, 3);
	//usleep(2700000);
	
	glutSwapBuffers(); //swap the buffers     
}


void ca3Dbase::reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(10, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void ca3Dbase::keyboard(unsigned char key, int x, int y)
{
	if (key == 'a')
	{
		xvel += 1.0;
	}

	if (key == 's')
	{
		xvel -= 1.0;
	}

	if (key == 'd')
	{
		yvel += 1.0;
	}

	if (key == 'f')
	{
		yvel -= 1.0;
	}
	if (key == 'g')
	{
		zvel += 1.0;
	}

	if (key == 'h')
	{
		zvel -= 1.0;
	}

	if (key == 'j')
	{
		zpos += 1.0;
	}

	if (key == 'k')
	{
		zpos -= 1.0;
	}

	if (key == 'z')
	{
		xvel = 0;
		yvel = 0;
		zvel = 0;
	}
}

int ca3Dbase::run(int argc, char **argv)
{
	ca3Dglobal::CurrentCA = this;

	initglut(argc, argv);
	initspace(size, wrap);
	initgraphics();
	initcamera();

	glutMainLoop(); //call the main loop
	return 0;
}

void ca3Dbase::start()
{
	initspace(size, wrap);
}
