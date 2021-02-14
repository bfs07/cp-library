/// Problem: How many distinct colors in the subtree of u?

vector<int> sub_sz(const int root_idx, const vector<vector<int>> &adj) {
  vector<int> sub(adj.size());
  function<int(int, int)> dfs = [&](const int u, const int p) {
    sub[u] = 1;
    for (int v : adj[u])
      if (v != p)
        sub[u] += dfs(v, u);
    return sub[u];
  };
  dfs(root_idx, -1);
  return sub;
}

vi color(MAXN), b(MAXN);
vector<int> sz;
int ans[MAXN];
vector<vector<int>> adj(MAXN);

set<int> dfs(int u, int p, int l) {
  int idx = -1, val = -1;
  for (int v : adj[u]) {
    if (v == p)
      continue;
    if (sz[v] > val) {
      val = sz[v];
      idx = v;
    }
  }

  set<int> s;
  if (idx != -1)
    // precalculate the answer for the biggest subtree and keep the results
    s = dfs(idx, u, l + 1);

  // idx now contains the index of the node of the biggest subtree
  for (int v : adj[u]) {
    if (v == p || v == idx)
      continue;
    // precalculate the answer for small subtrees
    for (int x : dfs(v, u, l + 1))
      s.emplace(x);
  }

  s.emplace(color[u]);
  ans[u] = s.size();
  return s;
}

/// MODIFY TO WORK WITH DISCONNECTED GRAPHS!!!
///
/// Time Complexity: O(n log n)
void precalculate() {
  sz = sub_sz(1, adj);
  dfs(1, -1, 0);
}