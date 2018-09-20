struct Point {
	double x,y,z;
	Point() { }
	Point (double x, double y, double z): x(x), y(y), z(z) {}
	bool operator-(const Point &a) const {
		return (x-a.x,y-a.y,z-a.z);
	}
	bool operator !=(const Point& a) const {
      return (x != a.x || y != a.y);
    }

    bool operator <(const Point &a) const{
      if(x == a.x)
        return y < a.y;
      return x < a.x;    
    }
};
