/// Problem: How many nodes in each depth in the subtree of u?

void combine(map<int, int> &a, map<int, int> &b) {
  if (a.size() < b.size())
    swap(a, b);
  for (auto [k, val] : b)
    a[k] += val;
}

vector<vector<int>> adj(MAXN);

map<int, int> dfs(int u, int p, int l) {
  map<int, int> mp;
  for (int v : adj[u]) {
    if (v != p) {
      auto tmp = dfs(v, u, l + 1);
      combine(mp, tmp);
    }
  }

  mp[l]++;
  // the map mp contains the answer here
  return mp;
}