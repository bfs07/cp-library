class Centroid {
private:
  int it = 1, _vertex;
  vector<int> vis, used, sub, _parent;
  vector<vector<int>> _tree;

  int dfs(const int u, int &cnt, const vector<vector<int>> &adj) {
    vis[u] = it;
    ++cnt;
    sub[u] = 1;
    for (const int v : adj[u])
      if (vis[v] != it && !used[v])
        sub[u] += dfs(v, cnt, adj);
    return sub[u];
  }

  int find_centroid(const int u, const int cnt,
                    const vector<vector<int>> &adj) {
    vis[u] = it;

    bool valid = true;
    int max_sub = -1;
    for (const int v : adj[u]) {
      if (vis[v] == it || used[v])
        continue;
      if (sub[v] > cnt / 2)
        valid = false;
      if (max_sub == -1 || sub[v] > sub[max_sub])
        max_sub = v;
    }

    if (valid && cnt - sub[u] <= cnt / 2)
      return u;
    return find_centroid(max_sub, cnt, adj);
  }

  int find_centroid(const int u, const vector<vector<int>> &adj) {
    // counts the number of vertices
    int cnt = 0;

    // set up sizes and nodes in current subtree
    dfs(u, cnt, adj);
    ++it;

    const int ctd = find_centroid(u, cnt, adj);
    ++it;
    used[ctd] = true;
    return ctd;
  }

  int build_tree(const int u, const vector<vector<int>> &adj) {
    const int ctd = find_centroid(u, adj);

    for (const int v : adj[ctd]) {
      if (used[v])
        continue;
      const int ctd_v = build_tree(v, adj);
      _tree[ctd].emplace_back(ctd_v);
      _tree[ctd_v].emplace_back(ctd);
      _parent[ctd_v] = ctd;
    }

    return ctd;
  }

  void allocate(const int n) {
    vis.resize(n);
    _parent.resize(n, -1);
    sub.resize(n);
    used.resize(n);
    _tree.resize(n);
  }

public:
  /// Constructor that creates the centroid tree.
  ///
  /// Time Complexity: O(n * log(n))
  Centroid(const int root_idx, const vector<vector<int>> &adj) {
    allocate(adj.size());
    _vertex = build_tree(root_idx, adj);
  }

  /// Returns the centroid of the whole tree.
  int vertex() { return _vertex; }

  int parent(const int u) { return _parent[u]; }

  vector<vector<int>> tree() { return _tree; };
};