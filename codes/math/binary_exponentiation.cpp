int bin_pow(const int n, int p) {
  assert(p >= 0);
  int ans = 1;
  int cur_pow = n;

  while (p) {
    if (p & 1)
      ans = (ans * cur_pow) % MOD;

    cur_pow = (cur_pow * cur_pow) % MOD;
    p >>= 1;
  }

  return ans;
}