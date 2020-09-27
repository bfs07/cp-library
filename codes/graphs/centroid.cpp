/// Returns the centroids of the tree which can contains at most 2.
///
/// Time complexity: O(n)
vector<int> centroid(const int n, const int indexed_from,
                     const vector<vector<int>> &adj) {
  vector<int> centers, sz(n + indexed_from);
  function<void(int, int)> dfs = [&](const int u, const int p) {
    sz[u] = 1;
    bool is_centroid = true;
    for (const int v : adj[u]) {
      if (v == p)
        continue;
      dfs(v, u);
      sz[u] += sz[v];
      if (sz[v] > n / 2)
        is_centroid = false;
    }
    if (n - sz[u] > n / 2)
      is_centroid = false;
    if (is_centroid)
      centers.emplace_back(u);
  };
  dfs(indexed_from, -1);
  return centers;
}