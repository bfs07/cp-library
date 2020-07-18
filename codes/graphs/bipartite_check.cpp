/// Time Complexity: O(V + E)
bool is_bipartite(const int src, const vector<vector<int>> &adj) {
  vector<int> color(adj.size(), -1);
  queue<int> q;

  color[src] = 1;
  q.emplace(src);
  while (!q.empty()) {
    const int u = q.front();
    q.pop();

    for (const int v : adj[u]) {
      if (color[v] == color[u])
        return false;
      else if (color[v] == -1) {
        color[v] = !color[u];
        q.emplace(v);
      }
    }
  }
  return true;
}