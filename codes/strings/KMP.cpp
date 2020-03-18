vector<int> pi(const string &s) {
  int n = s.size();
  vector<int> pi(n);

  int l = 0, r = 1;
  while (r < n) {
    if (s[l] == s[r]) {
      l++;
      pi[r] = l;
      r++;
    } else {
      if (l == 0) {
        pi[r] = 0;
        r++;
      } else
        l = pi[l - 1];
    }
  }
  return pi;
}

// returns the index of first occurence of a pat in a txt
int kmp(const string &txt, const string &pat) {
  int n = txt.size(), m = pat.size();

  int t = 0, p = 0;
  vector<int> pi_pat = pi(pat);
  // vector<int> occ;

  while (t < n) {

    if (txt[t] == pat[p]) {
      t++, p++;
      if (p == m) {
        return t - m;
        // if you want to continue searching
        // occ.pb(t - m);
        // p = pi_pat[p - 1];
      }
    } else {
      if (p == 0) {
        t++;
      } else {
        p = pi_pat[p - 1];
      }
    }
  }
  return -1;
  // return occ;
}