void dfs(int v, const vector<vector<int>> &adj, vector<int> &parent) {
  for (int u : adj[v]) {
    if (u != parent[v]) {
      parent[u] = v;
      dfs(u, adj, parent);
    }
  }
}

// IT MUST BE INDEXED BY 0.
/// Returns prueffer code of the tree.
///
/// Time Complexity: O(V)
vector<int> pruefer_code(const vector<vector<int>> &adj) {
  int n = adj.size();
  vector<int> parent(n);
  parent[n - 1] = -1;
  dfs(n - 1, adj, parent);

  int ptr = -1;
  vector<int> degree(n);
  for (int i = 0; i < n; i++) {
    degree[i] = adj[i].size();
    if (degree[i] == 1 && ptr == -1)
      ptr = i;
  }

  vector<int> code(n - 2);
  int leaf = ptr;
  for (int i = 0; i < n - 2; i++) {
    int next = parent[leaf];
    code[i] = next;
    if (--degree[next] == 1 && next < ptr)
      leaf = next;
    else {
      ptr++;
      while (degree[ptr] != 1)
        ptr++;
      leaf = ptr;
    }
  }

  return code;
}
