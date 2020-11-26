/// Returns the resulting polynomial after convolution of polynomials a and b.
///
/// Time Complexity: O(a.size() * b.size())
vector<int> convolution(const vector<int> &a, const vector<int> &b) {
  const int n = a.size(), m = b.size();
  vector<int> ans(n + m - 1);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      ans[i + j] += a[i] * b[j];
  return ans;
}