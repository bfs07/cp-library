/// INDEXED FROM 0!!!!!
int count_cycles(vector<vector<int>> &adj) {
  const int n = adj.size();
  vector<int> rep(n);

  auto comp = [&](int u, int v) {
    return adj[u].size() == adj[v].size() ? u < v
                                          : adj[u].size() > adj[v].size();
  };

  // Constains edges (u, v) in the original graph such that comp is true.
  vector<vector<int>> g(n);
  for (int u = 0; u < n; ++u)
    for (const int v : adj[u])
      if (comp(u, v))
        g[u].emplace_back(v);

  vector<int> cnt(n), vis(n);
  // Contains some cycles of length 4 and 3 (idk if contains all)
  // from the graph
  vector<vector<int>> cycles;

  int ans = 0;
  for (int u = 0; u < n; u++) {
    // Counting Squares:
    for (int to1 : g[u]) {
      cnt[to1] = 0;
      rep[to1] = -1;
      for (int to2 : adj[to1]) {
        rep[to2] = -1;
        cnt[to2] = 0;
      }
    }
    for (int to1 : g[u])
      for (int to2 : adj[to1]) {
        if (comp(u, to2)) {
          ans += cnt[to2];
          ++cnt[to2];

          if (rep[to2] != -1)
            cycles.push_back({u, to1, to2, rep[to2]});
          rep[to2] = to1;
        }
      }

    // Finding Triangles:
    for (int to : adj[u])
      vis[to] = 1;
    for (int to1 : g[u])
      for (int to2 : g[to1])
        if (vis[to2])
          cycles.push_back({u, to1, to2});
    for (int to : adj[u])
      vis[to] = 0;
  }

  return ans;
}
