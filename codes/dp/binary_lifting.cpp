// clang-format off
// #define COST
class Binary_Lifting {
private:
  const int NEUTRAL_VALUE = 0;
  // Up to ~~ 1e9
  const int MAXIMUM_POW = 30;
  vector<int> lg;
  const int n;
  vector<vector<int>> nxt, cost;

  int combine(const int a, const int b) { return a + b; }

  void build_log_array() {
    lg.resize(n + 1);
    for (int i = 2; i <= n; i++)
      lg[i] = lg[i / 2] + 1;
  }

  void allocate() {
    // initializes a matrix [n][lg n] with -1
    build_log_array();
    nxt.resize(MAXIMUM_POW, vector<int>(n + 1, -1));
    #ifdef COST
    cost.resize(MAXIMUM_POW, vector<int>(n + 1, NEUTRAL_VALUE));
    #endif
  }

  void build_nxt() {
    for (int j = 1; j < nxt.size(); j++)
      for (int i = 0; i < nxt.front().size(); i++)
        if (nxt[j - 1][i] != -1) {
          nxt[j][i] = nxt[j - 1][nxt[j - 1][i]];
          #ifdef COST
          cost[j][i] = combine(cost[j - 1][i], cost[j - 1][nxt[j - 1][i]]);
          #endif
        }
  }

public:
  Binary_Lifting(const vector<int> &nxt
  #ifdef COST
               , const vector<int> &cost
  #endif
    ) : n(nxt.size()) {
    allocate();
    this->nxt[0] = nxt;
#ifdef COST
    this->cost[0] = cost;
    assert(nxt.size() == cost.size());
#endif
    build_nxt();
  }

  /// Advance k steps from x.
  ///
  /// Time Complexity: O(log(k))
  int go_nxt(int x, int k) {
    for (int i = 0; k > 0; i++, k >>= 1)
      if (k & 1) {
        x = nxt[i][x];
        if (x == -1)
          return -1;
      }
    return x;
  }

  #ifdef COST
  /// Compute the cost after k steps from x.
  ///
  /// Time Complexity: O(log(k))
  int compute_cost(int x, int k) {
    assert(k < (1 << MAXIMUM_POW));
    int ans = 0;
    for (int i = 0; k > 0; i++, k >>= 1)
      if (k & 1) {
        ans += cost[i][x];
        x = nxt[i][x];
        if (x == -1)
          return -1;
      }
    return ans;
  }
  #endif
};
// clang-format on