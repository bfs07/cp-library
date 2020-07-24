// Global vector used in the class.
vector<int> hash_base;

class Hash {
  /// Prime numbers to be used in mod operations
  const vector<int> m = {1000000007, 1000000009};

  vector<vector<int>> hash_table;
  vector<vector<int>> pot;
  // size of the string
  const int n;

private:
  static int mod(int n, int m) {
    n %= m;
    if (n < 0)
      n += m;
    return n;
  }

  /// Time Complexity: O(1)
  pair<int, int> hash_query(const int l, const int r) {
    vector<int> ans(m.size());

    if (l == 0) {
      for (int i = 0; i < m.size(); i++)
        ans[i] = hash_table[i][r];
    } else {
      for (int i = 0; i < m.size(); i++)
        ans[i] =
            mod((hash_table[i][r] - hash_table[i][l - 1] * pot[i][r - l + 1]),
                m[i]);
    }

    return {ans.front(), ans.back()};
  }

  /// Time Complexity: O(m.size())
  void build_base() {
    if (!hash_base.empty())
      return;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(CHAR_MAX, INT_MAX);
    hash_base.resize(m.size());
    for (int i = 0; i < hash_base.size(); ++i)
      hash_base[i] = distribution(gen);
  }

  /// Time Complexity: O(n)
  void build_table(const string &s) {
    pot.resize(m.size(), vector<int>(this->n));
    hash_table.resize(m.size(), vector<int>(this->n));

    for (int i = 0; i < m.size(); i++) {
      pot[i][0] = 1;
      hash_table[i][0] = s[0];
      for (int j = 1; j < this->n; j++) {
        hash_table[i][j] =
            mod(s[j] + hash_table[i][j - 1] * hash_base[i], m[i]);
        pot[i][j] = mod(pot[i][j - 1] * hash_base[i], m[i]);
      }
    }
  }

public:
  /// Constructor thats builds the hash and pot tables and the hash_base vector.
  ///
  /// Time Complexity: O(n)
  Hash(const string &s) : n(s.size()) {
    build_base();
    build_table(s);
  }

  /// Returns the hash from l to r.
  ///
  /// Time Complexity: O(1) -> Actually O(number_of_primes)
  pair<int, int> query(const int l, const int r) {
    assert(0 <= l), assert(l <= r), assert(r < this->n);
    return hash_query(l, r);
  }
};
