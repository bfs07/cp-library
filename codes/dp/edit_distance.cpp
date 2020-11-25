/// Returns the minimum number of operations (insert, remove and delete) to
/// convert a into b.
///
/// Time Complexity: O(a.size() * b.size())
int edit_distance(const string &a, const string &b) {
  int n = a.size(), m = b.size();
  int dp[2][n + 1];
  memset(dp, 0, sizeof dp);
  for (int i = 0; i <= n; i++)
    dp[0][i] = i;
  for (int i = 1; i <= m; i++)
    for (int j = 0; j <= n; j++) {
      if (j == 0)
        dp[i & 1][j] = i;
      else if (a[j - 1] == b[i - 1])
        dp[i & 1][j] = dp[(i & 1) ^ 1][j - 1];
      else
        dp[i & 1][j] = 1 + min({dp[(i & 1) ^ 1][j], dp[i & 1][j - 1],
                                dp[(i & 1) ^ 1][j - 1]});
    }
  return dp[m & 1][n];
}