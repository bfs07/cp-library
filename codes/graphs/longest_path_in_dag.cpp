/// Requires topological_sort.cpp

/// Returns a vector with the maximal distance from src (must be 0 or 1) to
/// every node or a maximal path from src to (n - 1).
///
/// Time Complexity: O(n)
vector<int> longest_path_in_dag(const int src, const vector<vector<int>> &adj) {
  const int n = adj.size();
  vector<int> dp(n, -1), prev(n, -1);
  dp[src] = 0;
  for (int u : topological_sort(src, adj))
    for (int v : adj[u])
      if (dp[u] != -1 && dp[u] + 1 > dp[v]) {
        dp[v] = dp[u] + 1;
        prev[v] = u;
      }

  // Returns the longest path to each node
  // return dp;

  vector<int> path;
  // Assuming that the last node is the node (n - 1)
  int cur = n - 1;
  while (cur != -1) {
    path.emplace_back(cur);
    cur = prev[cur];
  }
  reverse(path.begin(), path.end());
  // Returns the maximal path from src to (n - 1)
  return path;
}