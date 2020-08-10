struct Matrix {
  static constexpr int N = 2, M = 2;
  static constexpr int MOD = 1e9 + 7;
  array<array<int, M>, N> mat = {};

  Matrix identity() {
    assert(N == M);
    Matrix mat_identity;
    for (int i = 0; i < N; ++i)
      mat_identity.mat[i][i] = 1;
    return mat_identity;
  }

  Matrix operator*(const Matrix &other) const {
    assert(mat.front().size() == other.mat.size());
    Matrix ans;
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < M; ++j)
        for (int k = 0; k < M; ++k)
          ans.mat[i][j] = (ans.mat[i][j] + mat[i][k] * other.mat[k][j]) % MOD;
    return ans;
  }

  Matrix expo(int p) {
    assert(p >= 0);
    Matrix ans = identity();
    Matrix cur_power;
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