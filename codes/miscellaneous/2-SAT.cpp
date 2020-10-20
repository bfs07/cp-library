// REQUIRES SCC code

// OBS: INDEXED FROM 0
class SAT {
private:
  vector<vector<int>> adj;
  int n;

public:
  // Contains the value for an possible answer. Take care, depending on the
  // implementation the value of the i-th variable may be negative or positive.
  vector<bool> ans;

  SAT(int n) {
    this->n = n;
    adj.resize(2 * n);
    ans.resize(n);
  }

  //  (X v Y)  = (~X -> Y) & (~Y -> X)
  void add_or(int x, bool pos_x, int y, bool pos_y) {
    assert(0 <= x), assert(x < n);
    assert(0 <= y), assert(y < n);
    adj[(x << 1) ^ (pos_x ^ 1)].emplace_back((y << 1) ^ pos_y);
    adj[(y << 1) ^ (pos_y ^ 1)].emplace_back((x << 1) ^ pos_x);
  }

  // (X xor Y) = (X v Y) & (~X v ~Y)
  // for this function the result is always 0 1 or 1 0
  void add_xor(int x, bool pos_x, int y, bool pos_y) {
    assert(0 <= x), assert(x < n);
    assert(0 <= y), assert(y < n);
    add_or(x, y, pos_x, pos_y);
    add_or(x, y, pos_x ^ 1, pos_y ^ 1);
  }

  /// Checks whether the system is feasible or not.
  ///
  /// Time Complexity: O(n)
  bool check() {
    SCC scc(2 * n, 0, adj);
    for (int i = 0; i < n; i++) {
      if (scc.comp[(i << 1) | 1] == scc.comp[(i << 1) | 0])
        return false;
      ans[i] = (scc.comp[(i << 1) | 1] < scc.comp[(i << 1) | 0]);
    }
    return true;
  }
};
