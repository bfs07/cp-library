/// Builds the pi array for the KMP algorithm.
///
/// Time Complexity: O(n)
vector<int> pi(const string &pat) {
  vector<int> ans(pat.size() + 1, -1);
  int i = 0, j = -1;
  while (i < pat.size()) {
    while (j >= 0 && pat[i] != pat[j])
      j = ans[j];
    ++i, ++j;
    ans[i] = j;
  }
  return ans;
}

/// Returns the occurrences of a pattern in a text.
///
/// Time Complexity: O(n + m)
vector<int> kmp(const string &txt, const string &pat) {
  vector<int> p = pi(pat);
  vector<int> ans;

  for (int i = 0, j = 0; i < txt.size(); ++i) {
    while (j >= 0 && pat[j] != txt[i])
      j = p[j];
    if (++j == pat.size()) {
      ans.emplace_back(i);
      j = p[j];
    }
  }
  return ans;
}