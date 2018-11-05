struct PT 
{   
  double x, y;  
  PT() {}  
  PT(double x, double y) : x(x), y(y) {}  
  PT(const PT &p) : x(p.x), y(p.y) {}  
  PT operator +(const PT &p)  const {          return PT(x+p.x, y+p.y); }  
  PT operator -(const PT &p)  const { return PT(x-p.x, y-p.y); }  
  PT operator *(double c)     const { return PT(x*c,   y*c  ); }
  bool operator ==(const pto &a) const {
	return ((x == a.x) && (y == a.y));}
};
