struct Line {
  Point a, b;
  Line() {}
  Line(Point x, Point y): a(x), b(y) {};
};

int sgn(double x) {
    if(abs(x) < 1e-8)   return 0;
    return x > 0 ? 1 : -1;
}
inline double sqr(double x) {   return x * x;   }

double dis_point_segment(const Point p, const Point s, const Point t) {
  if( sgn(dot(p-s, t-s)) < 0) return (p-s).norm();
  if( sgn(dot(p-t, s-t)) < 0) return (p-t).norm();
  return abs(det(s-p, t-p) / dist(s, t));
}