inline int mod(int x, const int MOD) {
  x %= MOD;
  if (x < 0)
    x += MOD;
  return x;
}

tuple<int, int, int> extended_gcd(int a, int b) {
  int x = 0, y = 1, x1 = 1, y1 = 0;
  while (a != 0) {
    const int q = b / a;
    tie(x, x1) = make_pair(x1, x - q * x1);
    tie(y, y1) = make_pair(y1, y - q * y1);
    tie(a, b) = make_pair(b % a, a);
  }
  return make_tuple(b, x, y);
}

/// Returns the smallest number x such that:
/// x % num[0] = rem[0],
/// x % num[1] = rem[1],
/// ..................
/// x % num[n - 1] = rem[n - 1]
/// It also works when gcd(rem[i], rem[j]) != 1
///
/// Time Complexity: O(n*log(n))
int crt(vector<int> &rem, const vector<int> &md) {
  const int n = rem.size();
  for (int i = 0; i < n; i++)
    rem[i] = mod(rem[i], md[i]);
  int ans = rem.front(), LCM = md.front();
  for (int i = 1; i < n; i++) {
    int x, g;
    tie(g, x, ignore) = extended_gcd(LCM, md[i]);
    if ((rem[i] - ans) % g != 0)
      return -1;
    ans =
        mod(ans + x * (rem[i] - ans) / g % (md[i] / g) * LCM, LCM * md[i] / g);
    // lcm of LCM, md[i]
    LCM = LCM / g * md[i];
  }
  return ans;
}