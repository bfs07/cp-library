// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
int onSegment(Point p, Point q, Point r) {
  if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
    return true; 
  return false;
}
/* PODE SER RETIRADO
int onSegmentNotBorda(Point p, Point q, Point r) {
    if (q.x < max(p.x, r.x) && q.x > min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
         return true;
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y < max(p.y, r.y) && q.y > min(p.y, r.y))
         return true; 
    return false;
}
*/
// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r) {
  int val = (q.y - p.y) * (r.x - q.x) -
            (q.x - p.x) * (r.y - q.y);
  if (val == 0) return 0;  // colinear
  return (val > 0)? 1: 2; // clock or counterclock wise
}
// The main function that returns true if line segment 'p1p2'
// and 'q1q2' intersect.
int doIntersect(Point p1, Point p2, Point q1, Point q2) {
  // Find the four orientations needed for general and
  // special cases
  int o1 = orientation(p1, p2, q1);
  int o2 = orientation(p1, p2, q2);
  int o3 = orientation(q1, q2, p1);
  int o4 = orientation(q1, q2, p2);
 
  // General case
  if (o1 != o2 && o3 != o4) return 2;

/* PODE SER RETIRADO
  if(o1 == o2 && o2 == o3 && o3 == o4 && o4 == 0) {
    //INTERCEPTAM EM RETA
    if(onSegmentNotBorda(p1,q1,p2) || onSegmentNotBorda(p1,q2,p2)) return 1;
    if(onSegmentNotBorda(q1,p1,q2) || onSegmentNotBorda(q1,p2,q2)) return 1;
  }
*/
  // Special Cases (INTERCEPTAM EM PONTO)
  // p1, p2 and q1 are colinear and q1 lies on segment p1p2
  if (o1 == 0 && onSegment(p1, q1, p2)) return 2;
  // p1, p2 and q1 are colinear and q2 lies on segment p1p2
  if (o2 == 0 && onSegment(p1, q2, p2)) return 2;
  // q1, q2 and p1 are colinear and p1 lies on segment q1q2
  if (o3 == 0 && onSegment(q1, p1, q2)) return 2;   
   // q1, q2 and p2 are colinear and p2 lies on segment q1q2
  if (o4 == 0 && onSegment(q1, p2, q2)) return 2;
  return false; // Doesn't fall in any of the above cases
} 
// OBS: SE (C2/A2 == C1/A1) SÃO COLINEARES
