// Asymptotic complexity: O(n log n).
struct Point {
	double x, y;
	bool operator <(const Point &p) const {
		return x < p.x || (x == p.x && y < p.y);
		/* a impressao será em prioridade por mais a esquerda, mais 
		   abaixo, e antihorário pelo cross abaixo */
	}
};

double cross(const Point &O, const Point &A, const Point &B) {
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

vector<Point> convex_hull(vector<Point> P) {
	int n = P.size(), k = 0;
	vector<Point> H(2 * n);
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
	return H;
}
