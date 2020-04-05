vector<pair<int, int>> sub(MAXN, pair<int, int>(0, 0));

void subu(int u, int p) {
  for (const pair<int, int> x : adj[u]) {
    int v = x.first, w = x.second;
    if (v == p)
      continue;
    subu(v, u);
    if (sub[v].first + w > sub[u].first) {
      swap(sub[u].first, sub[u].second);
      sub[u].first = sub[v].first + w;
    } else if (sub[v].first + w > sub[u].second) {
      sub[u].second = sub[v].first + w;
    }
  }
}

/// Contains the maximum distance to the node i
vector<int> ans(MAXN);

void dfs(int u, int d, int p) {
  ans[u] = max(d, sub[u].first);
  for (const pair<int, int> x : adj[u]) {
    int v = x.first, w = x.second;
    if (v == p)
      continue;
    if (sub[v].first + w == ans[u]) {
      dfs(v, max(d, sub[u].second) + w, u);
    } else {
      dfs(v, ans[u] + w, u);
    }
  }
}