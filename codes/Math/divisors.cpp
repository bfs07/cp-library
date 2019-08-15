// OBS: EACH NUMBER HAS AT MOST ∛N DIVISORS
vector<int> divisors(int n) {
  vector<int> ans;
  for (int i=1; i * i <= n; i++) {
    if (n%i==0) {
      // If divisors are equal, print only one
      if (n/i == i)
        ans.pb(i);
      else // Otherwise print both
        ans.pb(i), ans.pb(n/i);
    }
  }
  return ans;
}
