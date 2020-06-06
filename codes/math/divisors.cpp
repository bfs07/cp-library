/// OBS: Each number has at most ∛N divisors
/// THE NUMBERS ARE NOT SORTED!!!
///
/// Time Complexity: O(sqrt(n))
vector<int> divisors(int n) {
  vector<int> ans;
  for (int i = 1; i * i <= n; i++) {
    if (n % i == 0) {
      if (n / i == i)
        ans.emplace_back(i);
      else
        ans.emplace_back(i), ans.emplace_back(n / i);
    }
  }
  // sort(ans.begin(), ans.end());
  return ans;
}
