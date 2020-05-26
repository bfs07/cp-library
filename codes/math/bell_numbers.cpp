/// Number of ways to partition a set.
/// For example, the set {a, b, c}.
/// It can be partitioned in five ways: {(a) (b) (c)},{(a, b), (c)},
/// {(a, c)(b)}, {(b, c), a}, {(a, b, c)}.
///
/// Time Complexity: O(n * n)
int bellNumber(int n) {
  int bell[n + 1][n + 1];
  bell[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    bell[i][0] = bell[i - 1][i - 1];

    for (int j = 1; j <= i; j++)
      bell[i][j] = bell[i - 1][j - 1] + bell[i][j - 1];
  }
  return bell[n][0];
}
