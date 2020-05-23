/// Put n = n + 1 for 1 based.
void floyd_warshall(const int n) {
  // OBS: Always assign adj[i][i] = 0.
  for (int i = 0; i < n; i++)
    adj[i][i] = 0;

  for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
}
