double ptoReta(double x1, double y1, double x2,double y2,double pointX, double pointY, double *ptox,double *ptoy){
  double diffX = x2 - x1;
  double diffY = y2 - y1;
  if ((diffX == 0) && (diffY == 0)) {
    diffX = pointX - x1;
    diffY = pointY - y1;
    //se os dois sao pontos
    return hypot(pointX - x1,pointY - y1);
  }
  double t = ((pointX - x1) * diffX + (pointY - y1) * diffY) / 
                  (diffX * diffX + diffY * diffY);
  if (t < 0) {
    //point is nearest to the first point i.e x1 and y1
    // Ex:     _______________    .
    // cord do pto na reta = pto inicial(x1,y1);
    *ptox = x1, *ptoy = y1;
    diffX = pointX - x1;
    diffY = pointY - y1;
  } else if (t > 1) {
    //point is nearest to the end point i.e x2 and y2
    // Ex : .    _________________
    // cord do pto na reta = pto final(x2,y2);
    *ptox = x2, *ptoy = y2;
    diffX = pointX - x2;
    diffY = pointY - y2;
  } else  {
      //if perpendicular line intersect the line segment.
      // pto nao esta mais proximo de uma das bordas do segmento
      // Ex:              .
      //                  |
      //                  |(Ângulo Reto)      
      //________________________________________
      // cord x do pto na reta = (x1 + t * diffX)
      // cord y do pto na reta = (y1 + t * diffY)
    *ptox = (x1 + t * diffX), *ptoy = (y1 + t * diffY);
    diffX = pointX - (x1 + t * diffX);
    diffY = pointY - (y1 + t * diffY);
  }
  //returning shortest distance
  return sqrt(diffX * diffX + diffY * diffY);
}
