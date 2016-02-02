class Color
{
	public:
		GLfloat rgb[3];
		GLfloat alpha;

		Color() : Color(0, 0, 0, 1)
		{

		}

		Color(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
		{
			//rgb = new GLfloat[3];
			rgb[0] = r;
			rgb[1] = g;
			rgb[2] = b;
			alpha  = a;
		}
		
		~Color()
		{		
			//delete rgb;
		}
};
