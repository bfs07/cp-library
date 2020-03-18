// Outra forma de produto vetorial
// reta ab,ac se for zero e colinear
// se for < 0 entao antiHorario, > 0 horario
bool ehcol(pto a,pto b,pto c) {
  return ((b.y-a.y)*(c.x-a.x) - (b.x-a.x)*(c.y-a.y));
}
---------------------------------------
//Produto vetorial AB x AC, se for zero e colinear
int cross(pto A, pto B, pto C){
  pto AB, AC;
  AB.x = B.x-A.x;
  AB.y = B.y-A.y;
  AC.x = C.x-A.x;
  AC.y = C.y-A.y;
  int cross = AB.x*AC.y-AB.y * AC.x;
  return cross;
}

// OBS: DEFINE ÁREA DE QUADRILÁTERO FORMADO PELAS RETAS, A ÁREA DO TRIÂNGULO É A METADE
