string lcs(string &s, string &t) {

  int n = s.size(), m = t.size();

  s.insert(s.begin(), '#');
  t.insert(t.begin(), '$');

  vector<vector<int>> mat(n + 1, vector<int>(m + 1, 0));

  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      if(s[i] == t[j])
        mat[i][j] = mat[i - 1][j - 1] + 1;
      else
        mat[i][j] = max(mat[i - 1][j], mat[i][j - 1]);
    }
  }

  string ans;
  int i = n, j = m;
  while(i > 0 && j > 0) {
    if(s[i] == t[j])
      ans += s[i], i--, j--;
    else if(mat[i][j - 1] > mat[i - 1][j])
      j--;
    else
      i--;
  }

  reverse(ans.begin(), ans.end());
  return ans;
}