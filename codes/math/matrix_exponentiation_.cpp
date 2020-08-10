struct Matrix {
  static constexpr int MOD = 1e9 + 7;

  // // static matrix, if it's created multiple times, it's recommended
  // // to avoid TLE.
  // static constexpr int N = 2, M = 2;
  // array<array<int, M>, N> mat = {};
  // Matrix(const int n, const int m) {}

  // // dynamic matrix
  // int N, M;
  // vector<vector<int>> mat;
  // Matrix(const int n, const int m) : N(n), M(m) {
  //   mat.resize(n, vector<int>(m));
  // }

  /// Creates a n x n identity matrix.
  ///
  /// Time Complexity: O(n*n)
  Matrix identity() {
    assert(N == M);
    Matrix mat_identity(N, M);
    for (int i = 0; i < N; ++i)
      mat_identity.mat[i][i] = 1;
    return mat_identity;
  }

  /// Multiplies matrices mat and other.
  ///
  /// Time Complexity: O(mat.size() ^ 3)
  Matrix operator*(const Matrix &other) const {
    assert(mat.front().size() == other.mat.size());
    Matrix ans(N, M);
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < M; ++j)
        for (int k = 0; k < M; ++k)
          ans.mat[i][j] = (ans.mat[i][j] + mat[i][k] * other.mat[k][j]) % MOD;
    return ans;
  }

  /// Exponentiates the matrix mat to the power of p.
  ///
  /// Time Complexity: O((mat.size() ^ 3) * log2(p))
  Matrix expo(int p) {
    assert(p >= 0);
    Matrix ans = identity(), cur_power(N, M);
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