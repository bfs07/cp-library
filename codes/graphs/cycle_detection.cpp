/// Returns an arbitrary cycle in the graph.
///
/// Time Complexity: O(n)
vector<int> cycle(const int root_idx, const int n,
                  const vector<vector<int>> &adj) {
  vector<bool> vis(n + 1);
  vector<int> ans;
  function<int(int, int)> dfs = [&](const int u, const int p) {
    vis[u] = true;
    int val = -1;
    for (const int v : adj[u]) {
      if (v == p)
        continue;
      if (!vis[v]) {
        const int x = dfs(v, u);
        if (x != -1) {
          val = x;
          break;
        }
      } else {
        val = v;
        break;
      }
    }
    if (val != -1)
      ans.emplace_back(u);
    return (val == u ? -1 : val);
  };
  dfs(root_idx, -1);
  return ans;
}
