/// Time Complexity: O(V + E)
vector<int> topological_sort(const int indexed_from,
                             const vector<vector<int>> &adj) {
  const int n = adj.size();
  vector<int> in_degree(n, 0);

  for (int u = indexed_from; u < n; ++u)
    for (const int v : adj[u])
      in_degree[v]++;

  queue<int> q;
  for (int i = indexed_from; i < n; ++i)
    if (in_degree[i] == 0)
      q.emplace(i);

  int cnt = 0;
  vector<int> top_order;
  while (!q.empty()) {
    const int u = q.front();
    q.pop();

    top_order.emplace_back(u);
    ++cnt;

    for (const int v : adj[u])
      if (--in_degree[v] == 0)
        q.emplace(v);
  }

  if (cnt != n - indexed_from) {
    // There exists a cycle in the graph
    return vector<int>();
  }

  return top_order;
}
