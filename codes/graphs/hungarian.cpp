/// Returns a vector p of size n, where p[i] is the match for i
/// and the minimum cost.
///
/// Code copied from:
/// github.com/gabrielpessoa1/Biblioteca-Maratona/blob/master/code/Graph/Hungarian.cpp
///
/// Time Complexity: O(n^2 * m)
pair<vector<int>, int> solve(const vector<vector<int>> &matrix) {
  const int n = matrix.size();
  if (n == 0)
    return {vector<int>(), 0};
  const int m = matrix[0].size();
  assert(n <= m);
  vector<int> u(n + 1, 0), v(m + 1, 0), p(m + 1, 0), way, minv;
  for (int i = 1; i <= n; i++) {
    vector<int> minv(m + 1, INF);
    vector<int> way(m + 1, 0);
    vector<bool> used(m + 1, 0);
    p[0] = i;
    int k0 = 0;
    do {
      used[k0] = 1;
      int i0 = p[k0], delta = INF, k1;
      for (int j = 1; j <= m; j++) {
        if (!used[j]) {
          const int cur = matrix[i0 - 1][j - 1] - u[i0] - v[j];
          if (cur < minv[j]) {
            minv[j] = cur;
            way[j] = k0;
          }
          if (minv[j] < delta) {
            delta = minv[j];
            k1 = j;
          }
        }
      }
      for (int j = 0; j <= m; j++) {
        if (used[j]) {
          u[p[j]] += delta;
          v[j] -= delta;
        } else {
          minv[j] -= delta;
        }
      }
      k0 = k1;
    } while (p[k0]);
    do {
      const int k1 = way[k0];
      p[k0] = p[k1];
      k0 = k1;
    } while (k0);
  }
  vector<int> ans(n, -1);
  for (int j = 1; j <= m; j++) {
    if (!p[j])
      continue;
    ans[p[j] - 1] = j - 1;
  }
  return {ans, -v[0]};
}