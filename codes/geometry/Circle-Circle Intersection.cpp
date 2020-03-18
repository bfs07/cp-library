void circle_circle_intersection(/*...*/){
  double a, d, h, rx, ry,x2,y2;
  d = hypot(x1 - x0,y1 - y0);
  /* Determine the distance from point 0 to point 2. */
  a = ((r0*r0) - (r1*r1)+(d*d))/(2.0* d) ;
  /*Determine the coordinates of point 2*/ 
  x2 = x0 + (dx * a/d); y2 = y0 + (dy * a/d);
  /* Determine the distance from point 2 to either of the intersection points.*/   
  h = sqrt((r0*r0) - (a*a));
  /* Now determine the offsets of the intersection points from
   * point 2.*/
  rx = -dy * (h/d); ry = dx * (h/d);
  /* Determine the absolute intersection points. */
  *xi = x2 + rx;
  *xi_prime = x2 - rx;
  *yi = y2 + ry;
  *yi_prime = y2 - ry; 
}
