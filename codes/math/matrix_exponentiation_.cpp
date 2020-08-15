struct Matrix {
  static constexpr int MOD = 1e9 + 7;

  // static matrix, if it's created multiple times, it's recommended
  // to avoid TLE.
  static constexpr int MAXN = 4, MAXM = 4;
  array<array<int, MAXM>, MAXN> mat = {};
  int n, m;
  Matrix(const int n, const int m) : n(n), m(m) {}

  static int mod(int n) {
    n %= MOD;
    if (n < 0)
      n += MOD;
    return n;
  }

  /// Creates a n x n identity matrix.
  ///
  /// Time Complexity: O(n*n)
  Matrix identity() {
    assert(n == m);
    Matrix mat_identity(n, m);
    for (int i = 0; i < n; ++i)
      mat_identity.mat[i][i] = 1;
    return mat_identity;
  }

  /// Multiplies matrices mat and other.
  ///
  /// Time Complexity: O(mat.size() ^ 3)
  Matrix operator*(const Matrix &other) const {
    assert(m == other.n);
    Matrix ans(n, other.m);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        for (int k = 0; k < m; ++k)
          ans.mat[i][j] = mod(ans.mat[i][j] + mat[i][k] * other.mat[k][j]);
    return ans;
  }

  /// Exponentiates the matrix mat to the power of p.
  ///
  /// Time Complexity: O((mat.size() ^ 3) * log2(p))
  Matrix expo(int p) {
    assert(p >= 0);
    Matrix ans = identity(), cur_power(n, m);
    cur_power.mat = mat;
    while (p) {
      if (p & 1)
        ans = ans * cur_power;

      cur_power = cur_power * cur_power;
      p >>= 1;
    }
    return ans;
  }
};