int Dijkstra(int src, int dest, int n) {

  priority_queue<ii,vector <ii>,greater<ii>> pq; 
  vector<int> dist(n+1, INF); 
  // vector<vector<int> > parent(n+1);
  // for(int i = 0; i <= n; i++) 
  //   parent[i].pb(i);
  pq.push(make_pair(0, src));
  dist[src] = 0;

  while (!pq.empty()) {
    int u = pq.top().ss;
    pq.pop();
 
    for (ii x: adj[u]) {
      int v = x.ff;
      int w = x.ss;
 
      if (dist[u] + w < dist[v]) {
        // parent[v].clear();
        // parent[v].pb(u);
        dist[v] = dist[u] + w;
        pq.push(ii(dist[v], v));
      } 
      // else if(dist[u] + w == dist[v]) {
      //   parent[v].pb(u);
      // }
    }
  } 
  
  return dist[dest];
}