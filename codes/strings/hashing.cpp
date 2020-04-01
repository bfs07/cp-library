// OBS: CHOOSE THE OFFSET AND THE PRIMES BELOW!!
class Hash {
  /// Prime numbers to be used in mod operations
  vector<int> m = {1000000007, 1000000009};

  // static constexpr int OFFSET = 'a';
  // // Choose primes greater than the size of the alphabet.
  // vector<int> prime = {31, 37};

  // constexpr int OFFSET = 'A';
  // // Choose primes greater than the size of the alphabet.
  // Case the alphabet goes from 'A' to 'z'.
  // vector<int> prime = {61, 67};

  vector<vector<int>> hash_table;
  vector<vector<int>> pot;
  // size of the string
  int n;

 private:
  int mod(int n, int m) {
    n %= m;
    if(n < 0)
      n += m;
    return n;
  }

  /// Time Complexity: O(1)
  vector<int> hash_query(const int l, const int r) {
    vector<int> ans(m.size());

    if(l == 0) {
      for(int i = 0; i < m.size(); i++)
        ans[i] = hash_table[i][r];
    } else {
      for(int i = 0; i < m.size(); i++)
        ans[i] = mod((hash_table[i][r] - hash_table[i][l - 1] * pot[i][r - l + 1]), m[i]);
    }

    return ans;
  }

  /// Builds the hash table and the pot table.
  ///
  /// Time Complexity: O(n)
  void build(string &s) {
    pot.resize(m.size(), vector<int>(this->n));
    hash_table.resize(m.size(), vector<int>(this->n));
    // Remapping the string
    for(char &c: s)
      c -= OFFSET;

    for(int i = 0; i < m.size(); i++) {
      hash_table[i][0] = s[0];
      pot[i][0] = 1;
      for(int j = 1; j < this->n; j++) {
        hash_table[i][j] = (s[j] + hash_table[i][j - 1] * prime[i]) % m[i];
        pot[i][j] = (pot[i][j - 1] * prime[i]) % m[i];
      }
    }
  }

 public:
  /// Constructor that is responsible for building the hash table and pot table.
  ///
  /// Time Complexity: O(n)
  Hash(string &s) {
    assert(m.size() == prime.size());
    this->n = s.size();

    build(s);
  }

  /// Returns the hash from l to r.
  ///
  /// Time Complexity: O(1) -> Actually O(number_of_primes)
  vector<int> query(const int l, const int r) {
    assert(0 <= l); assert(l <= r); assert(r < this->n);
    return hash_query(l, r);
  }
};
