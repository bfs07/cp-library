#include <bits/stdc++.h>

using namespace std;

#define INF 1e18
#define pb push_back
#define ii pair<int,int>
#define OK cout<<"OK"<<endl
#define debug(x) cout << #x " = " << (x) << endl
#define ff first
#define ss second
#define int long long

struct pto {
  double x, y;
  bool operator <(const pto &p) const {
    return x < p.x || (x == p.x && y < p.y);
    /* a impressao será em prioridade por mais a esquerda, mais 
       abaixo, e antihorário pelo cross abaixo */
  }
};
double cross(const pto &O, const pto &A, const pto &B) {
  return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

vector<pto> lower, upper;

vector<pto> convex_hull(vector<pto> &P) {
  int n = P.size(), k = 0;
  vector<pto> H(2 * n);
  // Sort points lexicographically
  sort(P.begin(), P.end());
  // Build lower hull
  for (int i = 0; i < n; ++i) {
    // esse <= 0 representa sentido anti-horario, caso deseje mudar
    // trocar por >= 0
    while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) <= 0)
      k--;
    H[k++] = P[i];
  }
  // Build upper hull
  for (int i = n - 2, t = k + 1; i >= 0; i--) {
    // esse <= 0 representa sentido anti-horario, caso deseje mudar
    // trocar por >= 0
    while (k >= t && cross(H[k - 2], H[k - 1], P[i]) <= 0)
      k--;
    H[k++] = P[i];
  }
  H.resize(k);
  /* o último ponto do vetor é igual ao primeiro, atente para isso
  as vezes é necessário mudar */

  int j = 1;
  lower.pb(H.front());
  while(H[j].x >= H[j-1].x) {
    lower.pb(H[j++]);
  }

  int l = H.size()-1;
  while(l >= j) {
    upper.pb(H[l--]);
  }
  upper.pb(H[l--]);

  return H;
}

bool insidePolygon(pto p, vector<pto> &arr) {

  if(pair<double,double>(p.x, p.y) == pair<double,double>(lower[0].x, lower[0].y))
    return true;

  pto lo = {p.x, -(double)INF};
  pto hi = {p.x, (double)INF};
  auto itl = lower_bound(lower.begin(), lower.end(), lo);
  auto itu = lower_bound(upper.begin(), upper.end(), lo);

  if(itl == lower.begin() || itu == upper.begin()) {
    auto it  = lower_bound(arr.begin(), arr.end(), lo);
    auto it2 = lower_bound(arr.begin(), arr.end(), hi);
    it2--;
    if(it2 >= it && p.x == it-> x && it->x == it2->x && it->y <= p.y && p.y <= it2->y)
      return true;
    return false;
  }
  if(itl == lower.end() || itu == upper.end())  {
    return false;
  }

  auto ol = itl, ou = itu;
  ol--, ou--;
  if(cross(*ol, *itl, p) >= 0 && cross(*ou, *itu, p) <= 0)
    return true;

  auto it  = lower_bound(arr.begin(), arr.end(), lo);
  auto it2 = lower_bound(arr.begin(), arr.end(), hi);
  it2--;
  if(it2 >= it && p.x == it-> x && it->x == it2->x && it->y <= p.y && p.y <= it2->y)
    return true;

  return false;  

}

signed main () {
  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  double n, m, k;

  cin >> n >> m >> k;

  vector<pto> arr(n);

  for(pto &x: arr) {
    cin >> x.x >> x.y;
  }

  convex_hull(arr);

  pto p;

  int c = 0;
  while(m--) {
    cin >> p.x >> p.y;
    cout << (insidePolygon(p, arr) ? "dentro" : "fora") << endl;
  }
  
}