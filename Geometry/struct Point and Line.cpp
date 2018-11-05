int sgn(double x) {
    if(abs(x) < 1e-8)   return 0;
    return x > 0 ? 1 : -1;
}
inline double sqr(double x) {   return x * x;   }

struct Point {
    double x, y, z;
    Point() {};
    Point(double a, double b): x(a), y(b) {};
	  Point (double x, double y, double z): x(x), y(y), z(z) {}

    void input() {  scanf(" %lf %lf", &x, &y);  };
    friend Point operator+(const Point &a, const Point &b) {
        return Point(a.x + b.x, a.y + b.y);
    }
    friend Point operator-(const Point &a, const Point &b) {
        return Point(a.x - b.x, a.y - b.y);
    }
  	
  	bool operator !=(const Point& a) const {
        return (x != a.x || y != a.y);
    }

    bool operator <(const Point &a) const{
      if(x == a.x)
        return y < a.y;
      return x < a.x;    
    }

    double norm() {
        return sqrt(sqr(x) + sqr(y));
    }
};
double det(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}
double dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}
double dist(const Point &a, const Point &b) {
    return (a-b).norm();
}


struct Line {
    Point a, b;
    Line() {}
    Line(Point x, Point y): a(x), b(y) {};
};

double dis_point_segment(const Point p, const Point s, const Point t) {
    if(sgn(dot(p-s, t-s)) < 0) 
      return (p-s).norm();
    if(sgn(dot(p-t, s-t)) < 0) 
      return (p-t).norm();
    return abs(det(s-p, t-p) / dist(s, t));
}
