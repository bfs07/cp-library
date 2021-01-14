DSU dsu(MAXN);
/// Compress SCC's in a directed graph.
///
/// Time Complexity: O(V)
vector<vector<int>> compress(const int indexed_from,
                             const vector<vector<int>> &adj) {
  const int n = adj.size();
  SCC scc(n, indexed_from, adj);
  vector<unordered_set<int>> g(n);

  for (int i = 0; i < scc.number_of_comp; ++i)
    for (int v : scc.scc[i])
      dsu.Union(v, scc.scc[i].front());

  for (int u = indexed_from; u < n; ++u)
    for (int v : adj[u])
      if (dsu.Find(u) != dsu.Find(v))
        g[dsu.Find(u)].emplace(dsu.Find(v));

  vector<vector<int>> ret(n);
  for (int u = indexed_from; u < n; ++u)
    ret[u] = vector<int>(g[u].begin(), g[u].end());
  return ret;
}