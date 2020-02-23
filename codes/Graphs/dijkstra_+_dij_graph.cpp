class Dijkstra {
 private:
  int src, dest;
  int n;

 private:
  int calculate(vector<vector<ii>> &adj) {
    dist.resize(this->n + 1, INF);
    parent.resize(this->n + 1); 
    vector<int> vis(this->n + 1, 0);
    
    for(int i = 0; i <= this->n; i++) 
      parent[i].pb(i);
    
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    pq.push(make_pair(0, this->src));
    dist[this->src] = 0;

    while(!pq.empty()) {
      int u = pq.top().ss;
      pq.pop();
      if(vis[u])
        continue;
      vis[u] = true;

      for (ii x: adj[u]) {
        int v = x.ff;
        int w = x.ss;

        if(dist[u] + w < dist[v]) {
          parent[v].clear();
          parent[v].pb(u);
          dist[v] = dist[u] + w;
          pq.push(ii(dist[v], v));
        } 
        else if(dist[u] + w == dist[v]) {
          parent[v].pb(u);
        }
      }
    }

    return dist[dest];
  }

  // Use a vector vis in a DFS on the dijkstra graph 
  vector<vector<int>> gen_dij_graph() {
    vector<vector<int>> dijkstra_graph(this->n + 1);
    vector<bool> vis(this->n + 1);

    queue<int> q;
    q.push(this->dest);
    while(!q.empty()) {
      int v = q.front();
      q.pop();

      for(int u: parent[v]) {
        if(u == v)
          continue;
        dijkstra_graph[u].pb(v);
        if(!vis[u]) {
          q.push(u);
          vis[u] = true;
        }
      }
    }
    return dijkstra_graph;
  }

 public:
  int min_path;
  vector<int> dist;
  vector<vector<int>> parent;
  vector<vector<int>> dij_graph;

  Dijkstra(int n, int src, int dest, vector<vector<ii>> &adj) {
    this->n = n;
    this->src = src;
    this->dest = dest;
    this->min_path = this->calculate(adj);
    /// Generates the dijkstra graph with the parent vector
    this->dij_graph = this->gen_dij_graph();
    d_graph = this->dij_graph;
  }

  // Returns a path with minimum costs and a minimum length.
  vector<int> get_min_path() {
    vector<int> path;
    vector<int> pai(this->n + 1, -1);
    vector<int> d(this->n + 1, INF);

    queue<int> q;
    q.push(this->dest);
    d[this->dest] = 0;

    while(!q.empty()) {
      int v = q.front();
      q.pop();

      for(int u: parent[v]) {
        if(u == v)
          continue;
        if(d[v] + 1 < d[u]) {
          d[u] = d[v] + 1;
          pai[u] = v;
          q.push(u);
        }
      }
    }

    int cur = this->src;
    while(cur != -1) {
      path.pb(cur);
      cur = pai[cur];
    }

    return path;
  }
};