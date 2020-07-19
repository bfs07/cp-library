namespace graph {
unordered_set<int> ap;
vector<int> low, disc;
int cur_time = 1;

void dfs_ap(const int u, const int p, const vector<vector<int>> &adj) {
  low[u] = disc[u] = cur_time++;
  int children = 0;

  for (const int v : adj[u]) {
    // DO NOT ADD PARALLEL EDGES
    if (disc[v] == 0) {
      ++children;
      dfs_ap(v, u, adj);

      low[u] = min(low[v], low[u]);
      if (p == -1 && children > 1)
        ap.emplace(u);
      if (p != -1 && low[v] >= disc[u])
        ap.emplace(u);
    } else if (v != p)
      low[u] = min(low[u], disc[v]);
  }
}

void allocate(const int n) {
  low.resize(n, 0);
  disc.resize(n, 0);
}

/// THE GRAPH MUST BE UNDIRECTED!
///
/// Returns the vertices in which their removal disconnects the graph.
///
/// Time Complexity: O(V + E)
vector<int> articulation_points(const int indexed_from,
                                const vector<vector<int>> &adj) {
  allocate(adj.size());
  vector<int> ans;
  for (int u = indexed_from; u < adj.size(); ++u) {
    if (disc[u] == 0)
      dfs_ap(u, -1, adj);
    if (ap.count(u))
      ans.emplace_back(u);
  }
  return ans;
}
}; // namespace graph