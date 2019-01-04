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

