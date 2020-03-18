/// Returns the maximum path between the vertices 0 and n - 1 in a unweighted graph.
///
/// Time Complexity: O(V + E)
int maximum_path(int n) {
  vector<int> top_order = topological_sort(n);
  vector<int> pai(n, -1);
  if(top_order.empty())
    return -1;

  vector<int> dp(n);
  dp[0] = 1;
  for(int u: top_order)
    for(int v: adj[u])
      if(dp[u] && dp[u] + 1 > dp[v]) {
        dp[v] = dp[u] + 1;
        pai[v] = u;
      }

  if(dp[n - 1] == 0)
    return -1;

  vector<int> path;
  int cur = n - 1;
  while(cur != -1) {
    path.pb(cur);
    cur = pai[cur]; 
  }
  reverse(path.begin(), path.end());

  // cout << path.size() << endl;
  // for(int x: path) {
  //   cout << x + 1 << ' ';
  // }
  // cout << endl;

  return dp[n - 1];
}