// Intersecção de retas Ax + By = C    dados pontos (x1,y1) e (x2,y2)
A = y2-y1
B = x1-x2
C = A*x1+B*y1
//Retas definidas pelas equações:
A1x + B1y = C1
A2x + B2y = C2
//Encontrar x e y resolvendo o sistema
double det = A1*B2 - A2*B1;
if(det == 0){
  //Lines are parallel
}else{
  double x = (B2*C1 - B1*C2)/det;
  double y = (A1*C2 - A2*C1)/det;
}
