int bfs(int vt) {

  vector<int> dist(MAXN, INF);
  queue<pair<int, int>> q;

  q.emplace(vt, -1);
  dist[vt] = 0;

  int ans = INF;
  while (!q.empty()) {
    pair<int, int> aux = q.front();
    int u = aux.first, p = aux.second;
    q.pop();

    for (int v : adj[u]) {
      if (v == p)
        continue;
      if (dist[v] < INF)
        ans = min(ans, dist[u] + dist[v] + 1);
      else {
        dist[v] = dist[u] + 1;
        q.emplace(v, u);
      }
    }
  }

  return ans;
}

/// Returns the shortest cycle in the graph
///
/// Time Complexity: O(V^2)
int get_girth(int n) {
  int ans = INF;
  for (int u = 1; u <= n; u++)
    ans = min(ans, bfs(u));
  return ans;
}