// use struct point and line
double dist_point_segment(const Point p, const Point s, const Point t) {
    if(sgn(dot(p-s, t-s)) < 0) 
      return (p-s).norm();
    if(sgn(dot(p-t, s-t)) < 0) 
      return (p-t).norm();
    return abs(det(s-p, t-p) / dist(s, t));
}
