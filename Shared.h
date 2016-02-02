#ifndef SHARED_INCLUDES_HEADER
#define SHARED_INCLUDES_HEADER

#define RT 1.414213562
#define CS 80

#include <stdlib.h>
#include <GL/glut.h>
//#include <GL/gl.h>

#include <math.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

#include "Utilities.h"
#include "Color.h"
#include "Vector3d.h"
#include "Cursor.h"
#include "Space.h"
#include "Settings.h"
#include "Conway.h"
#include "Renderer.h"
#include "Seeds.h"

int main(int argc, char** args);

#endif
