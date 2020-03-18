// IT MUST BE INDEXED BY 0.
/// Returns the adjacency matrix of the decoded tree.
///
/// Time Complexity: O(V)
vector<vector<int>> pruefer_decode(const vector<int> &code) {

  int n = code.size() + 2;
  vector<vector<int>> adj = vector<vector<int>>(n, vector<int>());
  vector<int> degree(n, 1);
  for (int x : code)
    degree[x]++;

  int ptr = 0;
  while (degree[ptr] > 1)
    ++ptr;

  int nxt = ptr;
  for (int u : code) {
    adj[u].push_back(nxt);
    adj[nxt].push_back(u);

    if (--degree[u] == 1 && u < ptr)
      nxt = u;
    else {
      while (degree[++ptr] > 1)
        ;
      nxt = ptr;
    }
  }
  adj[n - 1].push_back(nxt);
  adj[nxt].push_back(n - 1);

  return adj;
}