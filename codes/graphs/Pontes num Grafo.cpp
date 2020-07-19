namespace graph {
int cur_time = 1;
vector<pair<int, int>> bg;
vector<int> disc;
vector<int> low;
vector<int> cycle;

void dfs_bg(const int u, int p, const vector<vector<int>> &adj) {
  low[u] = disc[u] = cur_time++;
  for (const int v : adj[u]) {
    if (v == p) {
      // checks parallel edges
      // IT'S BETTER TO REMOVE THEM!
      p = -1;
      continue;
    } else if (disc[v] == 0) {
      dfs_bg(v, u, adj);
      low[u] = min(low[u], low[v]);
      if (low[v] > disc[u])
        bg.emplace_back(u, v);
    } else
      low[u] = min(low[u], disc[v]);
    // checks if the vertex u belongs to a cycle
    cycle[u] |= (disc[u] >= low[v]);
  }
}

void init_bg(const int n) {
  cur_time = 1;
  bg = vector<pair<int, int>>();
  disc = vector<int>(n, 0);
  low = vector<int>(n, 0);
  cycle = vector<int>(n, 0);
}

/// THE GRAPH MUST BE UNDIRECTED!
///
/// Returns the edges in which their removal disconnects the graph.
///
/// Time Complexity: O(V + E)
vector<pair<int, int>> bridges(const int indexed_from,
                               const vector<vector<int>> &adj) {
  init_bg(adj.size());
  for (int u = indexed_from; u < adj.size(); ++u)
    if (disc[u] == 0)
      dfs_bg(u, -1, adj);

  return bg;
}
} // namespace graph