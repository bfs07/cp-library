bool Graph::isCyclicUtil(int v, bool vis[], int parent){
  // Mark the current node as vis
  vis[v] = true; 
  // Recur for all the vertices adjacent to this vertex
  vector<int>::iterator i;
  for (i = adj[v].begin(); i != adj[v].end(); ++i) {
    // If an adjacent is not vis, then recur for that adjacent
    if (!vis[*i]){
      if(isCyclicUtil(*i,vis,v))
        return true;
    } 
    // If an adjacent is vis and not parent of current vertex,
    // then there is a cycle.
    else if (*i != parent)
      return true;
  }
  return false;
} 
// Returns true if the graph contains a cycle, else false.
bool isCyclic(int V) {
  // Mark all the vertices as not vis and not part of recursion
  // stack
  bool vis[V];
  memset(vis, 0, sizeof(vis));
 
  // Call the recursive helper function to detect cycle in different
  for (int u = 0; u < V; u++)
    if (!vis[u]) 
      if(isCyclicUtil(u, vis, -1))
        return true;
 
  return false;
}
