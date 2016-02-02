

class Cursor
{
	// cube cursor
	public:
		Color* acolor;
		Color* specular;
		double radius;
		Vector3d* pos;
		GLfloat* shine;
		Vector3d* orientation;
		double length;
		
		Cursor(Color* c, Color* sp, double r, Vector3d* d, GLfloat* sh, Vector3d* o)
		{
			acolor   = c;
			specular = sp;
			radius   = r;
			pos      = d;
			shine    = sh;
			orientation = o; // rotational angle of the cube
			length = 2;
		}
		
		~Cursor()
		{
			delete acolor;
			delete specular;
			delete pos;
			delete orientation;
		}
		
		void setcolor(Color* x)
		{
			acolor = x;
		}			
		
		void linerel(Vector3d* disp)
		{
			int i;
			double m;
			Vector3d* temp2;
			Vector3d* temp1;
			orientation = disp;
			m = disp->mag();			
			orientation->scalarp(1 / m);
			glTranslatef(pos->x ,pos->y, pos->z);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, acolor->rgb);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular->rgb);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);	
			glTranslatef(-pos->x ,-pos->y, -pos->z);
			for (i = 0; i < m / (radius*2.0f); i++)
			{				
				pset();									
				temp2 = orientation->copyv();
				temp2->scalarp(radius * 2);
				temp1 = pos->vadd(temp2);	
				pos->x = temp1->x;
				pos->y = temp1->y;
				pos->z = temp1->z;				
				delete temp1;
				delete temp2;
			}
							
		}		
		
		void moveabs(Vector3d* dest)
		{			
			pos->x = dest->x;			
			pos->y = dest->y;			
			pos->z = dest->z;			
			
		}
		
		void moverel(Vector3d* disp)
		{			
			Vector3d* temp2;
			temp2 = pos;
			pos = temp2->vadd(disp);		
			//delete temp2;
		}
		
		void pset()
		{			
			Vector3d* orth;
			Vector3d* unitx = new Vector3d(1, 0, 0);
			double rotang;
			const double degs = 360/(2 * 3.14f);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, acolor->rgb);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular->rgb);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);
						
			glTranslatef(pos->x ,pos->y, pos->z);						
			orth = unitx->cross(orientation);			
			rotang = unitx->bangle(orientation);
			rotang *= degs;			
			glRotatef(rotang, orth->x, orth->y, orth->z);
			glutSolidCube(radius * 2);
			//glutSolidSphere(radius, 10,10);
			glRotatef(-rotang, orth->x, orth->y, orth->z);
			glTranslatef(-pos->x, -pos->y, -pos->z);
			delete unitx;
			delete orth;
		}		
};
