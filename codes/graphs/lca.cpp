// #define DIST
// #define COST
/// UNCOMMENT ALSO THE LINE BELOW FOR COST!

// clang-format off
class LCA {
private:
  int n;
  // INDEXED from 0 or 1??
  int indexed_from;
  /// Store all log2 from 1 to n
  vector<int> lg;
  // level of the i-th node (height)
  vector<int> level;
  // matrix to store the ancestors of each node in power of 2 levels
  vector<vector<int>> anc;
  #ifdef DIST
  vector<int> dist;
  #endif
  #ifdef COST
  // int NEUTRAL_VALUE = -INF; // MAX COST
  // int combine(const int a, const int b) {return max(a, b);}
  
  // int NEUTRAL_VALUE = INF; // MIN COST
  // int combine(const int a, const int b) {return min(a, b);}
  vector<vector<int>> cost;
  #endif

private:
  void allocate() {
    // initializes a matrix [n][lg n] with -1
    this->build_log_array();
    this->anc.resize(n + 1, vector<int>(lg[n] + 1, -1));
    this->level.resize(n + 1, -1);
    #ifdef DIST
    this->dist.resize(n + 1, 0);
    #endif
    #ifdef COST
    this->cost.resize(n + 1, vector<int>(lg[n] + 1, NEUTRAL_VALUE));
    #endif
  }

  void build_log_array() {
    this->lg.resize(this->n + 1);
    for (int i = 2; i <= this->n; i++)
      this->lg[i] = this->lg[i / 2] + 1;
  }

  void build_anc() {
    for (int j = 1; j < anc.front().size(); j++)
      for (int i = 0; i < anc.size(); i++)
        if (this->anc[i][j - 1] != -1) {
          this->anc[i][j] = this->anc[this->anc[i][j - 1]][j - 1];
          #ifdef COST
          this->cost[i][j] =
              combine(this->cost[i][j - 1], this->cost[anc[i][j - 1]][j - 1]);
          #endif
        }
  }

  void build_weighted(const vector<vector<pair<int, int>>> &adj) {
    this->dfs_LCA_weighted(this->indexed_from, -1, 1, 0, adj);
    this->build_anc();
  }

  void dfs_LCA_weighted(const int u, const int p, const int l, const int d,
                        const vector<vector<pair<int, int>>> &adj) {
    this->level[u] = l;
    this->anc[u][0] = p;
    #ifdef DIST
    this->dist[u] = d;
    #endif

    for (const pair<int, int> &x : adj[u]) {
      int v = x.first, w = x.second;
      if (v == p)
        continue;
      #ifdef COST
      this->cost[v][0] = w;
      #endif
      this->dfs_LCA_weighted(v, u, l + 1, d + w, adj);
    }
  }

  void build_unweighted(const vector<vector<int>> &adj) {
    this->dfs_LCA_unweighted(this->indexed_from, -1, 1, 0, adj);
    this->build_anc();
  }

  void dfs_LCA_unweighted(const int u, const int p, const int l, const int d,
                          const vector<vector<int>> &adj) {
    this->level[u] = l;
    this->anc[u][0] = p;
    #ifdef DIST
    this->dist[u] = d;
    #endif

    for (const int v : adj[u]) {
      if (v == p)
        continue;
      this->dfs_LCA_unweighted(v, u, l + 1, d + 1, adj);
    }
  }

  // go up k levels from x
  int lca_go_up(int x, int k) {
    for (int i = 0; k > 0; i++, k >>= 1)
      if (k & 1) {
        x = this->anc[x][i];
        if (x == -1)
          return -1;
      }
    return x;
  }

  #ifdef COST
  /// Query between the an ancestor of v (p) and v. It returns the
  /// max/min edge between them.
  int lca_query_cost_in_line(int v, int p) {
    assert(this->level[v] >= this->level[p]);

    int k = this->level[v] - this->level[p];
    int ans = NEUTRAL_VALUE;

    for (int i = 0; k > 0; i++, k >>= 1)
      if (k & 1) {
        ans = combine(ans, this->cost[v][i]);
        v = this->anc[v][i];
      }

    return ans;
  }
  #endif

  int get_lca(int a, int b) {
    // a is below b
    if (this->level[b] > this->level[a])
      swap(a, b);

    const int logg = lg[this->level[a]];
    // putting a and b in the same level
    for (int i = logg; i >= 0; i--)
      if (this->level[a] - (1 << i) >= this->level[b])
        a = this->anc[a][i];

    if (a == b)
      return a;

    for (int i = logg; i >= 0; i--)
      if (this->anc[a][i] != -1 && this->anc[a][i] != this->anc[b][i]) {
        a = this->anc[a][i];
        b = this->anc[b][i];
      }

    return anc[a][0];
  }

public:
  /// Builds an weighted graph.
  ///
  /// Time Complexity: O(n*log(n))
  explicit LCA(const vector<vector<pair<int, int>>> &adj,
               const int indexed_from)
      : n(adj.size()), indexed_from(indexed_from) {
    this->allocate();
    this->build_weighted(adj);
  }

  /// Builds an unweighted graph.
  ///
  /// Time Complexity: O(n*log(n))
  explicit LCA(const vector<vector<int>> &adj, const int indexed_from)
      : n(adj.size()), indexed_from(indexed_from) {
    this->allocate();
    this->build_unweighted(adj);
  }

  /// Goes up k levels from v. If it passes the root, returns -1.
  ///
  /// Time Complexity: O(log(k))
  int go_up(const int v, const int k) {
    assert(indexed_from <= v), assert(v < this->n + indexed_from);
    return this->lca_go_up(v, k);
  }

  /// Returns the parent of v in the LCA dfs from 1.
  ///
  /// Time Complexity: O(1)
  int parent(int v) {
    assert(indexed_from <= v), assert(v < this->n + indexed_from);
    return this->anc[v][0];
  }

  /// Returns the LCA of a and b.
  ///
  /// Time Complexity: O(log(n))
  int query_lca(const int a, const int b) {
    assert(indexed_from <= min(a, b)),
        assert(max(a, b) < this->n + indexed_from);
    return this->get_lca(a, b);
  }

  #ifdef DIST
  /// Returns the distance from a to b. When the graph is unweighted, it is
  /// considered 1 as the weight of the edges.
  ///
  /// Time Complexity: O(log(n))
  int query_dist(const int a, const int b) {
    assert(indexed_from <= min(a, b)),
        assert(max(a, b) < this->n + indexed_from);
    return this->dist[a] + this->dist[b] - 2 * this->dist[this->get_lca(a, b)];
  }
  #endif

  #ifdef COST
  /// Returns the max/min weight edge from a to b.
  ///
  /// Time Complexity: O(log(n))
  int query_cost(const int a, const int b) {
    assert(indexed_from <= min(a, b)),
        assert(max(a, b) < this->n + indexed_from);
    const int l = this->query_lca(a, b);
    return combine(this->lca_query_cost_in_line(a, l),
                   this->lca_query_cost_in_line(b, l));
  }
  #endif
};
// clang-format on