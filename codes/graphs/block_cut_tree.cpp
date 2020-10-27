// based on kokosha's implementation.
/// INDEXED FROM ZERO!!!!!
class BCT {
  vector<vector<pair<int, int>>> adj;
  vector<pair<int, int>> edges;
  /// Stores the edges in the i-th component.
  vector<vector<int>> comps;
  /// Stores the vertices in the i-th component.
  vector<vector<int>> vert_in_comp;
  int cur_time = 0;
  vector<int> disc, conv;
  vector<vector<int>> adj_bct;
  const int n;

  /// Finds the biconnected components.
  int dfs(const int x, const int p, stack<int> &st) {
    int low = disc[x] = ++cur_time;
    for (const pair<int, int> &e : adj[x]) {
      const int v = e.first, idx = e.second;
      if (idx != p) {
        if (!disc[v]) {    // if haven't passed
          st.emplace(idx); // disc[x] < low -> bridge
          const int low_at = dfs(v, idx, st);
          low = min(low, low_at);
          if (disc[x] <= low_at) {
            comps.emplace_back();
            vector<int> &tmp = comps.back();
            for (int y = -1; y != idx; st.pop())
              tmp.emplace_back(y = st.top());
          }
        } else if (disc[v] < disc[x]) // back_edge
          low = min(low, disc[v]), st.emplace(idx);
      }
    }
    return low;
  }

  /// Splits the graph into biconnected components.
  void split() {
    adj_bct.resize(n + edges.size() + 1);
    stack<int> st;
    for (int i = 0; i < n; ++i)
      if (!disc[i])
        dfs(i, -1, st);

    vector<bool> in(n);
    for (const vector<int> &comp : comps) {
      vert_in_comp.emplace_back();
      for (const int e : comp) {
        const int u = edges[e].first, v = edges[e].second;
        if (!in[u])
          in[u] = 1, vert_in_comp.back().emplace_back(u);
        if (!in[v])
          in[v] = 1, vert_in_comp.back().emplace_back(v);
      }
      for (const int e : comp)
        in[edges[e].first] = in[edges[e].second] = 0;
    }
  }

  /// Algorithm: It compresses the biconnected components into one vertex. Then
  /// it creates a bipartite graph with the original vertices on the left and
  /// the bcc's on the right. After that, it connects with an edge the i-th
  /// vertex on the left to the j-th on the right if the vertex i is present in
  /// the j-th bcc. Note that articulation points will be present in more than
  /// one component.
  void build() {
    // next new node to be used in bct
    int nxt = n;
    for (const vector<int> &vic : vert_in_comp) {
      for (const int u : vic) {
        adj_bct[u].emplace_back(nxt);
        adj_bct[nxt].emplace_back(u);
        conv[u] = nxt;
      }
      nxt++;
    }

    // if it's not an articulation point we can remove it from the bct.
    for (int i = 0; i < n; ++i)
      if (adj_bct[i].size() == 1)
        adj_bct[i].clear();
  }

  void init() {
    disc.resize(n);
    conv.resize(n);
    adj.resize(n);
  }

public:
  /// Pass the number of vertices to the constructor.
  BCT(const int n) : n(n) { init(); }

  /// Adds an bidirectional edge.
  void add_edge(const int u, const int v) {
    assert(0 <= min(u, v)), assert(max(u, v) < n), assert(u != v);
    adj[u].emplace_back(v, edges.size());
    adj[v].emplace_back(u, edges.size());
    edges.emplace_back(u, v);
  }

  /// Returns the bct tree. It builds the tree if it's not computed.
  ///
  /// Time Complexity: O(n + m)
  vector<vector<int>> tree() {
    if (adj_bct.empty()) // if it's not calculated.
      split(), build();
    return adj_bct;
  }

  /// Returns whether the vertex u is an articulation point or not.
  bool is_art_point(const int u) {
    assert(0 <= u), assert(u < n);
    assert(!adj_bct.empty()); // the tree method should've called before.
    return !adj_bct[u].empty();
  }

  /// Returns the corresponding vertex of the u-th vertex in the bct.
  int convert(const int u) {
    assert(0 <= u), assert(u < n);
    assert(!adj_bct.empty()); // the tree method should've called before.
    return adj_bct[u].empty() ? conv[u] : u;
  }
};