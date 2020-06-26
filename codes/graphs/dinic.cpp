class Dinic {
  struct Edge {
    const int v;
    // capacity (maximum flow) of the edge
    // if it is a reverse edge then its capacity should be equal to 0
    const int cap;
    // current flow of the graph
    int flow = 0;
    Edge(const int v, const int cap) : v(v), cap(cap) {}
  };

private:
  static constexpr int INF = 2e18;
  bool COMPUTED = false;
  int _max_flow;
  vector<Edge> edges;
  // holds the indexes of each edge present in each vertex.
  vector<vector<int>> adj;
  const int n;
  // src will be always 0 and sink n+1.
  const int src, sink;
  vector<int> level, ptr;

private:
  vector<vector<int>> _flow_table() {
    vector<vector<int>> table(n, vector<int>(n, 0));
    for (int u = 0; u <= sink; ++u)
      for (const int idx : adj[u])
        if (edges[idx].cap != 0)
          table[u][edges[idx].v] += edges[idx].flow;
    return table;
  }

  vector<int> _max_ind_set(const int max_left) {
    const vector<int> mvc = _min_vertex_cover(max_left);
    vector<bool> contains(n);
    for (const int v : mvc)
      contains[v] = true;
    vector<int> ans;
    // takes the complement of the vertex cover
    for (int i = 1; i < sink; ++i)
      if (!contains[i])
        ans.emplace_back(i);
    return ans;
  }

  void dfs_vc(const int u, vector<bool> &vis, const bool left,
              const vector<vector<int>> &paths) {
    vis[u] = true;
    for (const int idx : adj[u]) {
      const Edge &e = edges[idx];
      if (vis[e.v])
        continue;
      // saturated edges goes from right to left
      if (left && paths[u][e.v] == 0)
        dfs_vc(e.v, vis, left ^ 1, paths);
      // non-saturated edges goes from left to right
      else if (!left && paths[e.v][u] == 1)
        dfs_vc(e.v, vis, left ^ 1, paths);
    }
  }

  vector<int> _min_vertex_cover(const int max_left) {
    vector<bool> vis(n, false), saturated(n, false);
    const auto paths = flow_table();

    for (int i = 1; i <= max_left; ++i) {
      for (int j = max_left + 1; j < sink; ++j)
        if (paths[i][j] > 0) {
          saturated[i] = true;
          saturated[j] = true;
          break;
        }
      if (!saturated[i] && !vis[i])
        dfs_vc(i, vis, 1, paths);
    }

    vector<int> ans;
    for (int i = 1; i <= max_left; ++i)
      if (saturated[i] && !vis[i])
        ans.emplace_back(i);

    for (int i = max_left + 1; i < sink; ++i)
      if (saturated[i] && vis[i])
        ans.emplace_back(i);

    return ans;
  }

  void dfs_build_path(const int u, vector<int> &path,
                      vector<vector<int>> &table, vector<vector<int>> &ans,
                      const vector<vector<int>> &adj) {
    path.emplace_back(u);

    if (u == sink) {
      ans.emplace_back(path);
      return;
    }

    for (const int v : adj[u]) {
      if (table[u][v]) {
        --table[u][v];
        dfs_build_path(v, path, table, ans, adj);
        return;
      }
    }
  }

  vector<vector<int>> _compute_all_paths(const vector<vector<int>> &adj) {
    vector<vector<int>> table = flow_table();
    vector<vector<int>> ans;
    ans.reserve(_max_flow);

    for (int i = 0; i < _max_flow; i++) {
      vector<int> path;
      path.reserve(n);
      dfs_build_path(src, path, table, ans, adj);
    }

    return ans;
  }

  vector<pair<int, int>> _min_cut() {
    // checks if there's an edge from i to j.
    vector<vector<bool>> mat_adj(n, vector<bool>(n));
    vector<vector<int>> table(n, vector<int>(n));
    for (int u = 0; u <= sink; ++u)
      for (const int idx : adj[u])
        // checks if it's not a reverse edge
        if (edges[idx].cap != 0) {
          mat_adj[u][edges[idx].v] = true;
          // checks if its residual capacity is greater than zero.
          if (edges[idx].flow < edges[idx].cap)
            table[u][edges[idx].v] = 1;
        }

    vector<bool> vis(n);
    queue<int> q;

    q.push(src);
    vis[src] = true;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int v = 0; v < n; ++v)
        if (table[u][v] > 0 && !vis[v]) {
          q.push(v);
          vis[v] = true;
        }
    }

    vector<pair<int, int>> cut;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        if (vis[i] && !vis[j])
          // if there's an edge from i to j.
          if (mat_adj[i][j])
            cut.emplace_back(i, j);

    return cut;
  }

  void _add_edge(const int u, const int v, const int cap) {
    adj[u].emplace_back(edges.size());
    edges.emplace_back(v, cap);
    // adding reverse edge
    adj[v].emplace_back(edges.size());
    edges.emplace_back(u, 0);
  }

  bool bfs() {
    queue<int> q;
    memset(level.data(), -1, sizeof(*level.data()) * level.size());
    q.emplace(src);
    level[src] = 0;
    while (!q.empty()) {
      const int u = q.front();
      q.pop();
      for (const int idx : adj[u]) {
        const Edge &e = edges[idx];
        if (e.cap == e.flow || level[e.v] != -1)
          continue;
        level[e.v] = level[u] + 1;
        q.emplace(e.v);
      }
    }
    return (level[sink] != -1);
  }

  int dfs(const int u, const int cur_flow) {
    if (u == sink)
      return cur_flow;

    for (int &idx = ptr[u]; idx < adj[u].size(); ++idx) {
      Edge &e = edges[adj[u][idx]];
      if (level[u] + 1 != level[e.v] || e.cap == e.flow)
        continue;
      const int flow = dfs(e.v, min(e.cap - e.flow, cur_flow));
      if (flow == 0)
        continue;
      e.flow += flow;
      edges[adj[u][idx] ^ 1].flow -= flow;
      return flow;
    }
    return 0;
  }

  int compute() {
    int ans = 0;
    while (bfs()) {
      memset(ptr.data(), 0, sizeof(*ptr.data()) * ptr.size());
      while (const int cur = dfs(src, INF))
        ans += cur;
    }
    return ans;
  }

  void check_computed() {
    if (!COMPUTED) {
      COMPUTED = true;
      this->_max_flow = compute();
    }
  }

public:
  /// Constructor that makes assignments and allocations.
  ///
  /// Time Complexity: O(V)
  Dinic(const int n) : n(n + 2), src(0), sink(n + 1) {
    assert(n >= 0);

    adj.resize(this->n);
    level.resize(this->n);
    ptr.resize(this->n);
  }

  /// Returns the maximum independent set for the graph.
  /// An independent set represent a set of vertices such that they're not
  /// adjacent to each other.
  /// It is equal to the complement of the minimum vertex cover.
  ///
  /// Time Complexity: O(V)
  vector<int> max_ind_set(const int max_left) {
    this->check_computed();
    return this->_max_ind_set(max_left);
  }

  /// Returns the minimum vertex cover of a bipartite graph.
  /// A minimum vertex cover represents a set of vertices such that each edge of
  /// the graph is incident to at least one vertex of the graph.
  /// Pass the maximum index of a vertex on the left side as an argument.
  /// Algorithm used: codeforces.com/blog/entry/17534?#comment-223759
  ///
  /// Time Complexity: O(V)
  vector<int> min_vertex_cover(const int max_left) {
    this->check_computed();
    return this->_min_vertex_cover(max_left);
  }

  /// Computes all paths from src to sink.
  /// Add all edges from the original graph. Its weights should be equal to the
  /// number of edges between the vertices. Pass the adjacency list with
  /// repeated vertices if there are multiple edges.
  ///
  /// Time Complexity: O(max_flow*V)
  vector<vector<int>> compute_all_paths(const vector<vector<int>> &adj) {
    this->check_computed();
    return this->_compute_all_paths(adj);
  }

  /// Returns the edges present in the minimum cut of the graph.
  ///
  /// Time Complexity: O(V^2)
  vector<pair<int, int>> min_cut() {
    this->check_computed();
    return this->_min_cut();
  }

  /// Returns a table with the flow values for each pair of vertices.
  ///
  /// Time Complexity: O(V^2)
  vector<vector<int>> flow_table() {
    this->check_computed();
    return this->_flow_table();
  }

  /// Adds a directed edge between u and v and its reverse edge.
  ///
  /// Time Complexity: O(1);
  void add_to_sink(const int u, const int cap) {
    assert(!COMPUTED);
    assert(src <= u), assert(u < sink);
    assert(cap >= 0);
    this->_add_edge(u, sink, cap);
  }

  /// Adds a directed edge between u and v and its reverse edge.
  ///
  /// Time Complexity: O(1);
  void add_to_src(const int v, const int cap) {
    assert(!COMPUTED);
    assert(src < v), assert(v <= sink);
    assert(cap >= 0);
    this->_add_edge(src, v, cap);
  }

  /// Adds a directed edge between u and v and its reverse edge.
  ///
  /// Time Complexity: O(1);
  void add_edge(const int u, const int v, const int cap) {
    assert(!COMPUTED);
    assert(src <= u), assert(u <= sink);
    assert(cap >= 0);
    this->_add_edge(u, v, cap);
  }

  /// Computes the maximum flow for the network.
  ///
  /// Time Complexity: O(V^2*E) or O(E*sqrt(V)) for matching.
  int max_flow() {
    this->check_computed();
    return this->_max_flow;
  }
};