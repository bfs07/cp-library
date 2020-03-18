namespace matrix {
#define Matrix vector<vector<int>>
const int MOD = 1e9 + 7;

/// Creates an n x n identity matrix.
///
/// Time Complexity: O(n*n)
Matrix identity(const int n) {
  assert(n > 0);

  Matrix mat_identity(n, vector<int>(n, 0));

  for (int i = 0; i < n; i++)
    mat_identity[i][i] = 1;

  return mat_identity;
}

/// Multiplies matrices a and b.
///
/// Time Complexity: O(mat.size() ^ 3)
Matrix mult(const Matrix &a, const Matrix &b) {
  assert(a.front().size() == b.size());

  Matrix ans(a.size(), vector<int>(b.front().size(), 0));
  for (int i = 0; i < ans.size(); i++)
    for (int j = 0; j < ans.front().size(); j++)
      for (int k = 0; k < a.front().size(); k++)
        ans[i][j] = (ans[i][j] + a[i][k] * b[k][j]) % MOD;

  return ans;
}

/// Exponentiates the matrix mat to the power of p.
///
/// Time Complexity: O((mat.size() ^ 3) * log2(p))
Matrix expo(Matrix &mat, int p) {
  assert(p >= 0);

  Matrix ans = identity(mat.size());
  Matrix cur_power;
  cur_power.swap(mat);

  while (p) {
    if (p & 1)
      ans = mult(ans, cur_power);

    cur_power = mult(cur_power, cur_power);
    p >>= 1;
  }

  return ans;
}
}; // namespace matrix