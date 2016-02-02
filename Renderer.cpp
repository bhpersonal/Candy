#include "Shared.h"

Renderer* RendererGlobal::CurrentRenderer;

Renderer::Renderer(Conway* conway)
{
	this->space = conway->space;
	this->settings = conway->settings;
	this->conway = conway;

	initializeGlut();
	initializeGraphics();
	initializeCamera();
	initializePixels();
}


void Renderer::initializeGlut()
{
	char *myargv[1]; // https://www.opengl.org/discussion_boards/showthread.php/132736-How-to-call-glutInit%28%29-without-parameters
	int myargc = 1;
	myargv[0] = _strdup("Artificial life");
	glutInit(&myargc, myargv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH); //set the display to Double buffer, with depth
	glutInitWindowSize(2000, 1000); //set the window size
	glutInitWindowPosition(0, 0); //set the position of the window
	glutCreateWindow("Artificial Life"); //the caption of the window
	glutDisplayFunc(RendererGlobal::taketurn); //use the display function to draw everything
	glutIdleFunc(RendererGlobal::taketurn); //update any variables in display, display can be changed to anyhing, as long as you move the variables to be updated, in this case, angle++;
	glutReshapeFunc(RendererGlobal::reshape); //reshape the window accordingly
	glutKeyboardFunc(RendererGlobal::keyboard); //check the keyboard
}


void Renderer::initializeGraphics()
{
	yang = 0;
	zpos = space->extents[0] / 2 + 15;
	//xpos = -15;
	//ypos = -10;
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
	Vector3d* position2 = new Vector3d(0, 0, 0);
	Vector3d* orient2 = new Vector3d(1, 0, 0);
	Color* blue = new Color(0.0, 0.0, 1.0, 1.0);
	Color* white = new Color(0.0, 0.0, 0.0, 1.0);
	GLfloat* shine = new float(128.0f);
	cursor = new Cursor(blue, white, radius, position2, shine, orient2);
}

void Renderer::initializeCamera()
{
	xang = yang = zang = 0;
	xvel = yvel = zvel = 0;

	xang = 10.0;
	yang = -10.0;
	yvel = 0.0;
}

void Renderer::initializePixels()
{
	if (settings->renderMethod == RenderMethodExplodeHigherDimensions)
	{
		pixelVectors = new Vector3d[space->matrixSize];
		pixelColors = new Color[space->matrixSize];

		int renderableDimensions = 3;
		float buffer = .8;
		float scale = 1.0;

		float totalSizePerRenderableDimension[3] = { 1, 1, 1 };

		float* dimensionMultipliers = new float[space->dimensions];

		float maximumSizeOfRenderableDimensions = 0.0;
		for (int dimension = 0; dimension < space->dimensions; dimension++)
		{
			totalSizePerRenderableDimension[dimension % 3] *= (space->extents[dimension]) * (1.0 + buffer);
			if (totalSizePerRenderableDimension[dimension % 3] > maximumSizeOfRenderableDimensions)
				maximumSizeOfRenderableDimensions = totalSizePerRenderableDimension[dimension % 3];

			dimensionMultipliers[dimension] = totalSizePerRenderableDimension[dimension % 3];
		}

		scale = 1 / maximumSizeOfRenderableDimensions;

		scale *= 3; // Fudge factor to fit into camera settings

		int* zeroOrdinates = space->createOrdinates();
		int* ordinates = space->createOrdinates();
		for (int i = 0; i < space->matrixSize; i++)
		{
			// Could be made more efficient through caching
			pixelColors[i].rgb[0] = space->dimensions >= 1 ? ((float)ordinates[0] / (float)space->extents[0]) : .5f;
			pixelColors[i].rgb[1] = space->dimensions >= 2 ? ((float)ordinates[1] / (float)space->extents[1]) : .5f;
			pixelColors[i].rgb[2] = space->dimensions >= 3 ? ((float)ordinates[2] / (float)space->extents[2]) : .5f;
			pixelColors[i].alpha = 0.8;

			// Could be made more efficient through caching
			pixelVectors[i].x = 0.0;
			pixelVectors[i].y = 0.0;
			pixelVectors[i].z = 0.0;
			for (int dimension = 0; dimension < space->dimensions; dimension += 3)
			{
				pixelVectors[i].x += (((float)ordinates[dimension] / (float)space->extents[dimension]) - 0.5) * dimensionMultipliers[dimension];

				if (dimension + 1 < space->dimensions) {
					pixelVectors[i].y += (((float)ordinates[dimension + 1] / (float)space->extents[dimension + 1]) - 0.5) * dimensionMultipliers[dimension + 1];
				}
				if (dimension + 2 < space->dimensions) {
					pixelVectors[i].z += (((float)ordinates[dimension + 2] / (float)space->extents[dimension + 2]) - 0.5) * dimensionMultipliers[dimension + 2];
				}
			}
			pixelVectors[i].x *= scale;
			pixelVectors[i].y *= scale;
			pixelVectors[i].z *= scale;

			space->iterateOverOrdinates(ordinates, zeroOrdinates, space->extents);
		}

		delete ordinates;
		delete zeroOrdinates;
		delete dimensionMultipliers;

		cursor->radius  = scale * .9;
	}
}


void Renderer::takeTurn()
{
	conway->takeTurn();

	xang += xvel;
	yang += yvel;
	zang += zvel;
	render();
}

Renderer::~Renderer()
{
	delete cursor;
	delete pixelVectors;
	delete pixelColors;
}

void Renderer::run()
{
	RendererGlobal::CurrentRenderer = this;

	glutMainLoop(); //call the main loop

}

// TODO cleanup utlity function
void Renderer::drawString(void * font, char *s, float x, float y, float z){
	unsigned int i;

	glDisable(GL_LIGHTING);
	glRasterPos3f(x, y, z);
	glColor3f(1.0, 1.0, 0.0);
	for (i = 0; i < strlen(s); i++)
		glutBitmapCharacter(font, s[i]);

	glEnable(GL_LIGHTING);
}

// TODO better way or leave?
#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
	(std::ostringstream() << std::dec << x)).str()

void Renderer::render()
{
	Color* custom;
	Vector3d d(0, 0, 0);
	Vector3d ep(0, 0, 0);

	custom = new Color(0.4, 1.0, 0.2, 1.0);

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

	if (settings->renderMethod == RenderMethodExplodeHigherDimensions)
	{
		for (int i = 0; i < space->matrixSize; i++)
		{
			if (space->getCell(i) == 1) 
			{
				cursor->moveabs(&pixelVectors[i]);
				cursor->setcolor(&pixelColors[i]);
				cursor->pset(); // TODO - pixel shapes
			}
		}

		/*
		int renderableDimensions = 3;
		float buffer = .1; // 10% buffer
		float scale = 1.0;
		
		float totalSizePerRenderableDimension[3] = { 1, 1, 1 };

		float* dimensionMultipliers = new float[space->dimensions];

		float maximumSizeOfRenderableDimensions = 0.0;
		for (int dimension = 0; dimension < space->dimensions; dimension++) 
		{
			totalSizePerRenderableDimension[dimension % 3] *= (space->extents[dimension]) * (1.0 + buffer);
			if (totalSizePerRenderableDimension[dimension % 3] > maximumSizeOfRenderableDimensions)
				maximumSizeOfRenderableDimensions = totalSizePerRenderableDimension[dimension % 3];

			dimensionMultipliers[dimension] = totalSizePerRenderableDimension[dimension % 3];
		}

		scale = 1 / maximumSizeOfRenderableDimensions;

		int* zeroOrdinates = space->createOrdinates();
		int* ordinates = space->createOrdinates();
		for (int i = 0; i < space->matrixSize; i++)
		{
			unsigned char state = space->getCell(ordinates);
			if (state == 1) {

				// Could be made more efficient through caching
				custom->rgb[0] = space->dimensions >= 1 ? ((float)ordinates[0] / (float)space->extents[0]) : .5f;
				custom->rgb[1] = space->dimensions >= 2 ? ((float)ordinates[1] / (float)space->extents[1]) : .5f;
				custom->rgb[2] = space->dimensions >= 3 ? ((float)ordinates[2] / (float)space->extents[2]) : .5f;
				custom->alpha = 0.8;

				// Could be made more efficient through caching
				d.x = 0.0;
				d.y = 0.0;
				d.z = 0.0;
				for (int dimension = 0; dimension < space->dimensions; dimension += 3)
				{
					d.x += (((float)ordinates[dimension] / (float)space->extents[dimension]) - 0.5) * dimensionMultipliers[dimension];

					if (dimension + 1 < space->dimensions) {
						d.y += (((float)ordinates[dimension + 1] / (float)space->extents[dimension + 1]) - 0.5) * dimensionMultipliers[dimension + 1];
					}
					if (dimension + 2 < space->dimensions) {
						d.z += (((float)ordinates[dimension + 2] / (float)space->extents[dimension + 2]) - 0.5) * dimensionMultipliers[dimension + 2];
					}
				}
				d.x *= scale;
				d.y *= scale;
				d.z *= scale;

				cursor->moveabs(&d);
				cursor->setcolor(custom);
				cursor->pset(); // TODO - pixel shapes
			}

			space->iterateOverOrdinates(ordinates, zeroOrdinates, space->extents);
		}

		delete ordinates;
		delete zeroOrdinates;*/
	}
	else if (settings->renderMethod == RenderMethodMaxIntensity)
	{
		// TODO
	}
	else if (settings->renderMethod == RenderMethodMiddleSlice)
	{
		// TODO
	}

	glRotatef(-xang, 1.0f, 0.0f, 0.0f);
	glRotatef(-yang, 0.0f, 1.0f, 0.0f);
	glRotatef(-zang, 0.0f, 0.0f, 1.0f);

	std::stringstream ss;
	ss << conway->turn;
	drawString(GLUT_BITMAP_HELVETICA_18, (char*)ss.str().c_str(), 3, 3, 3);

	glutSwapBuffers();
}

void Renderer::reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(10, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void Renderer::keyboard(unsigned char key, int x, int y)
{
	if (key == 'a')
	{
		xvel += 1.0;
	}
	else if (key == 's')
	{
		xvel -= 1.0;
	}
	else if (key == 'd')
	{
		yvel += 1.0;
	}
	else if (key == 'f')
	{
		yvel -= 1.0;
	}
	else if (key == 'g')
	{
		zvel += 1.0;
	}
	else if (key == 'h')
	{
		zvel -= 1.0;
	}
	else if (key == 'j')
	{
		zpos += 1.0;
	}
	else if (key == 'k')
	{
		zpos -= 1.0;
	}
	else if (key == 'z')
	{
		xvel = 0;
		yvel = 0;
		zvel = 0;
	}
}

