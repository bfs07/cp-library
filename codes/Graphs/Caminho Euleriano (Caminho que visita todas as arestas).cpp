void DFSUtil(int v, bool vis[]) {
    // Mark the current node as vis and print it
    vis[v] = true;
 
    // Recur for all the vertices adjacent to this vertex
    vector<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
      if (!vis[*i])
        DFSUtil(*i, vis);
}
 
// Method to check if all non-zero degree vertices are connected.
// It mainly does DFS traversal starting from
bool isConnected() {
    // Mark all the vertices as not vis
    bool vis[V];
    int i;
    for (i = 0; i < V; i++)
      vis[i] = false;
 
    // Find a vertex with non-zero degree
    for (i = 0; i < V; i++)
      if (adj[i].size() != 0)
        break;
 
    // If there are no edges in the graph, return true
    if (i == V)
      return true;
 
    // Start DFS traversal from a vertex with non-zero degree
    DFSUtil(i, vis);
 
    // Check if all non-zero degree vertices are vis
    for (i = 0; i < V; i++)
      if (vis[i] == false && adj[i].size() > 0)
        return false;
 
    return true;
}
 
/* The function returns one of the following values
   0 --> If graph is not Eulerian
   1 --> If graph has an Euler path (Semi-Eulerian)
   2 --> If graph has an Euler Circuit (Eulerian)  */
int isEulerian() {
  // Check if all non-zero degree vertices are connected
  if (isConnected() == false)
    return 0;
 
  // Count vertices with odd degree
  int odd = 0;
  for (int i = 0; i < V; i++)
    if (adj[i].size() & 1)
      odd++;
 
  // If count is more than 2, then graph is not Eulerian
  if (odd > 2)
    return 0;
 
  // If odd count is 2, then semi-eulerian. If odd count is 0, then eulerian
  // Note that odd count can never be 1 for undirected graph
  return (odd) ? 1 : 2;
}
