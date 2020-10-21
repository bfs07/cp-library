// OBS: INDEXED FROM 0
// USE POS_X = 1 FOR POSITIVE CLAUSES AND 0 FOR NEGATIVE. OTHERWISE THE FINAL
// ANSWER ARRAY WILL BE FLIPPED.
class SAT {
private:
  vector<vector<int>> adj;
  int n;

public:
  SAT(const int n) : n(n) {
    adj.resize(2 * n);
    ans.resize(n);
  }

  //  (X v Y)  = (~X -> Y) & (~Y -> X)
  void add_or(const int x, const bool pos_x, const int y, const bool pos_y) {
    assert(0 <= x), assert(x < n), assert(0 <= y), assert(y < n);
    adj[(x << 1) ^ (pos_x ^ 1)].emplace_back((y << 1) ^ pos_y);
    adj[(y << 1) ^ (pos_y ^ 1)].emplace_back((x << 1) ^ pos_x);
  }

  // (X xor Y) = (X v Y) & (~X v ~Y)
  // for this operation the result is always 0 1 or 1 0
  void add_xor(const int x, const bool pos_x, const int y, const bool pos_y) {
    assert(0 <= x), assert(x < n), assert(0 <= y), assert(y < n);
    add_or(x, pos_x, y, pos_y);
    add_or(x, pos_x ^ 1, y, pos_y ^ 1);
  }

  vector<bool> ans;
  /// Checks whether the system is feasible or not. If it's feasible, it stores
  /// a satisfable answer in the array `ans`.
  ///
  /// Time Complexity: O(n)
  bool check() {
    SCC scc(2 * n, 0, adj);
    for (int i = 0; i < n; i++) {
      if (scc.comp[(i << 1) | 1] == scc.comp[(i << 1) | 0])
        return false;
      ans[i] = (scc.comp[(i << 1) | 1] > scc.comp[(i << 1) | 0]);
    }
    return true;
  }
};
