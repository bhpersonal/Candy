class Vector3d
{
	public:
		double x,y,z;

		Vector3d() : Vector3d(0, 0, 0)
		{
			
		}

		Vector3d(double a, double b, double c)
		{
			x = a;
			y = b;
			z = c;
		}
		
		double dp(Vector3d* v2)
		{
			double g;
			g = x*v2->x + y*v2->y + z*v2->z;
			
			return g;
		}
		
		double mag()
		{
			return pow(x*x + y*y + z*z, 0.5);
		}
		
		void scalarp(double f)
		{			
			x *= f;
			y *= f;
			z *= f;			
		}
		
		Vector3d* vadd(Vector3d* v2)
		{
			Vector3d* adder = new Vector3d(0,0,0);
			adder->x = v2->x + x;
			adder->y = v2->y + y;
			adder->z = v2->z + z;
			return adder;
		}
		
		double bangle(Vector3d* v)
		{			
			double g,h,i;
			g = this->dp(v);
			h = v->mag();						
			i = this->mag();						
			return acos(g / ( h * i)); // returns radians
		}
		
		Vector3d* cross(Vector3d* v)
		{
			Vector3d* i = new Vector3d(1,0,0);
			Vector3d* j = new Vector3d(0,1,0);
			Vector3d* k = new Vector3d(0,0,1);
			Vector3d* t1;
			Vector3d* t3;			
			
			i->scalarp(y*v->z - z*v->y);
			j->scalarp(z*v->x - x*v->z);
			t1 = i->vadd(j);
			k->scalarp(x*v->y - y*v->x);
			t3 = t1->vadd(k);
			delete i;
			delete j;
			delete k;
			delete t1;
			return t3;
		}
		
		Vector3d* copyv()
		{
			Vector3d* w = new Vector3d(0,0,0);
			w->x = x;
			w->y = y;
			w->z = z;
			return w;
		}
};


