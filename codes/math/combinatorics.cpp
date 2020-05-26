class Combinatorics {
private:
  static constexpr int MOD = 1e9 + 7;
  const int max_val;
  vector<int> _inv, _fat;

private:
  int mod(int x) {
    x %= MOD;
    if (x < 0)
      x += MOD;
    return x;
  }

  static int bin_pow(const int n, int p) {
    assert(p >= 0);
    int ans = 1;
    int cur_pow = n;

    while (p) {
      if (p & 1ll)
        ans = (ans * cur_pow) % MOD;

      cur_pow = (cur_pow * cur_pow) % MOD;
      p >>= 1ll;
    }

    return ans;
  }

  vector<int> build_inverse(const int max_val) {
    vector<int> inv(max_val + 1);
    inv[1] = 1;
    for (int i = 2; i <= max_val; ++i)
      inv[i] = mod(-MOD / i * inv[MOD % i]);
    return inv;
  }

  vector<int> build_fat(const int max_val) {
    vector<int> fat(max_val + 1);
    fat[0] = 1;
    for (int i = 1; i <= max_val; ++i)
      fat[i] = mod(i * fat[i - 1]);
    return fat;
  }

public:
  /// Builds both factorial and modular inverse array.
  ///
  /// Time Complexity: O(max_val)
  Combinatorics(const int max_val) : max_val(max_val) {
    assert(0 <= max_val), assert(max_val <= MOD);
    this->_inv = this->build_inverse(max_val);
    this->_fat = this->build_fat(max_val);
  }

  /// Returns the modular inverse of n % MOD.
  ///
  /// Time Complexity: O(log(MOD))
  static int inv_log(const int n) { return bin_pow(n, MOD - 2); }

  /// Returns the modular inverse of n % MOD.
  ///
  /// Time Complexity: O((n <= max_val ? 1 : log(MOD))
  int inv(const int n) {
    assert(0 <= n);
    if (n <= max_val)
      return this->_inv[n];
    else
      return inv_log(n);
  }

  /// Returns the factorial of n % MOD.
  int fat(const int n) {
    assert(0 <= n), assert(n <= max_val);
    return this->_fat[n];
  }

  /// Returns C(n, k) % MOD.
  ///
  /// Time Complexity: O(1)
  int choose(const int n, const int k) {
    assert(0 <= k), assert(k <= n), assert(n <= this->max_val);
    return mod(fat(n) * mod(inv(fat(k)) * inv(fat(n - k))));
  }
};