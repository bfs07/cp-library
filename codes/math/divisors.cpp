/// OBS: Each number has at most ∛N divisors
/// THE NUMBERS ARE NOT SORTED!!!
vector<int> divisors(int n) {
  vector<int> ans;
  for (int i = 1; i * i <= n; i++) {
    if (n % i == 0) {
      // If divisors are equal, print only one
      if (n / i == i)
        ans.emplace_back(i);
      else // Otherwise print both
        ans.emplace_back(i), ans.emplace_back(n / i);
    }
  }
  return ans;
}
