/// Problem: Given an array of n numbers split the array until get n subarrays
/// of one element. The cost of each split is the sum of values in the subarray.
///
/// Time Complexity: O(n^2)
void knuth() {
  // length of the cut
  for (int i = 0; i < n; ++i)
    // cutting from j to j + i
    for (int j = 0; j + i < n; ++j) {
      if (i == 0) {
        dp[j][i + j] = 0;
        idx[j][i + j] = j;
      } else {
        dp[j][j + i] = INF;
        // searching for the optimal place to cut
        for (int k = idx[j][j + i - 1]; k <= min(j + i - 1, idx[j + 1][i + j]);
             ++k) {
          int val = dp[j][k] + dp[k + 1][j + i] + sum(j, j + i);
          if (val < dp[j][j + i]) {
            dp[j][j + i] = val;
            idx[j][j + i] = k;
          }
        }
      }
    }
}