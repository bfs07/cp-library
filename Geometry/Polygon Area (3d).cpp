#include <bits/stdc++.h>

using namespace std;

struct point{
  double x,y,z;
  void operator=(const point & b){
    x = b.x;
    y = b.y;
    z = b.z;
  }
};

point cross(point a, point b){
  point ret;
  ret.x = a.y*b.z - b.y*a.z;
  ret.y = a.z*b.x - a.x*b.z;
  ret.z = a.x*b.y - a.y*b.x;
  return ret;
}

int main(){
  int num;
  cin >> num;
  point v[num];
  for(int i=0; i<num; i++) cin >> v[i].x >> v[i].y >> v[i].z;
  
  point cur;
  cur.x = 0, cur.y = 0, cur.z = 0;
  
  for(int i=0; i<num; i++){
    point res = cross(v[i], v[(i+1)%num]);
    cur.x += res.x;
    cur.y += res.y;
    cur.z += res.z;
  }
  
  double ans = sqrt(cur.x*cur.x + cur.y*cur.y + cur.z*cur.z);
  
  double area = abs(ans);
  
  cout << fixed << setprecision(9) << area/2. << endl; 
} 