namespace tree {
/// Returns a pair which contains the most distant vertex from src and the
/// value of this distance.
pair<int, int> bfs(const int src, const vector<vector<int>> &adj) {
  queue<tuple<int, int, int>> q;
  q.emplace(0, src, -1);
  int furthest = src, dist = 0;
  while (!q.empty()) {
    int d, u, p;
    tie(d, u, p) = q.front();
    q.pop();
    if (d > dist) {
      furthest = u;
      dist = d;
    }
    for (const int v : adj[u]) {
      if (v == p)
        continue;
      q.emplace(d + 1, v, u);
    }
  }
  return make_pair(furthest, dist);
}

/// Returns the length of the diameter and two vertices that belong to it.
///
/// Time Complexity: O(n)
tuple<int, int, int> diameter(const int root_idx,
                              const vector<vector<int>> &adj) {
  int ini = bfs(root_idx, adj).first, end, dist;
  tie(end, dist) = bfs(ini, adj);
  return {dist, ini, end};
}
}; // namespace tree