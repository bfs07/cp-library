// Based on: http://maratona.ic.unicamp.br/MaratonaVerao2020/lecture-b/20200122.pdf

class Functional_Graph {
 // FOR DIRECTED GRAPH
 private:
  void compute_cycle(int u, vector<int> &nxt, vector<bool> &vis) {
    int id_cycle = cycle_cnt++;
    int cur_id = 0;
    this->first[id_cycle] = u;
 
    while(!vis[u]) {
      vis[u] = true;
 
      this->cycle[id_cycle].push_back(u);
 
      this->in_cycle[u] = true;
      this->cycle_id[u] = id_cycle;
      this->id_in_cycle[u] = cur_id;
      this->near_in_cycle[u] = u;
      this->id_near_cycle[u] = id_cycle;
      this->cycle_dist[u] = 0;
 
      u = nxt[u];
      cur_id++;
    }
  }
 
  // Time Complexity: O(V)
  void build(int n, int indexed_from, vector<int> &nxt, vector<int> &in_degree) {
    queue<int> q;
    vector<bool> vis(n + indexed_from);
    for(int i = indexed_from; i < n + indexed_from; i++) {
      if(in_degree[i] == 0) {
        q.push(i);
        vis[i] = true;
      }
    }
 
    vector<int> process_order;
    process_order.reserve(n + indexed_from);
    while(!q.empty()) {
      int u = q.front();
      q.pop();
 
      process_order.push_back(u);
 
      if(--in_degree[nxt[u]] == 0) {
        q.push(nxt[u]);
        vis[nxt[u]] = true;
      }
    }
 
    int cycle_cnt = 0;
    for(int i = indexed_from; i < n + indexed_from; i++)
      if(!vis[i])
        compute_cycle(i, nxt, vis);
 
    for(int i = (int)process_order.size() - 1; i >= 0; i--) {
      int u = process_order[i];
 
      this->near_in_cycle[u] = this->near_in_cycle[nxt[u]];
      this->id_near_cycle[u] = this->id_near_cycle[nxt[u]];
      this->cycle_dist[u] = this->cycle_dist[nxt[u]] + 1;
    }
  }
 
  void allocate(int n, int indexed_from) {
    this->cycle.resize(n + indexed_from);
    this->first.resize(n + indexed_from);
 
    this->in_cycle.resize(n + indexed_from, false);    
    this->cycle_id.resize(n + indexed_from, -1);
    this->id_in_cycle.resize(n + indexed_from, -1);    
    this->near_in_cycle.resize(n + indexed_from);    
    this->id_near_cycle.resize(n + indexed_from);    
    this->cycle_dist.resize(n + indexed_from);    
  }
 
 public:
  Functional_Graph(int n, int indexed_from, vector<int> &nxt, vector<int> &in_degree) {
    this->allocate(n, indexed_from);
    this->build(n, indexed_from, nxt, in_degree);
  }
 
  // THE CYCLES ARE ALWAYS INDEXED BY ZERO!
 
  // number of cycles
  int cycle_cnt = 0;
  // Vertices present in the i-th cycle.
  vector<vector<int>> cycle;
  // first vertex of the i-th cycle
  vector<int> first;
 
  // The i-th vertex is present in any cycle?
  vector<bool> in_cycle;
  // id of the cycle that the vertex belongs. -1 if it doesn't belong to any cycle.
  vector<int> cycle_id;
  // Represents the id of the cycle of the i-th vertex. -1 if it doesn't belong to any cycle.
  vector<int> id_in_cycle;
  // Represents the id of the nearest vertex present in a cycle.
  vector<int> near_in_cycle;
  // Represents the id of the nearest cycle.
  vector<int> id_near_cycle;
  // Distance to the nearest cycle.
  vector<int> cycle_dist;
  // Represent the id of the component of the vertex.
  // Equal to id_near_cycle 
  vector<int> &comp = id_near_cycle;
};

class Functional_Graph {
 // FOR UNDIRECTED GRAPH
 private:
  void compute_cycle(int u, vector<int> &nxt, vector<bool> &vis, vector<vector<int>> &adj) {
    int id_cycle = cycle_cnt++;
    int cur_id = 0;
    this->first[id_cycle] = u;
 
    while(!vis[u]) {
      vis[u] = true;
 
      this->cycle[id_cycle].push_back(u);
      nxt[u] = find_nxt(u, vis, adj);
      if(nxt[u] == -1)
        nxt[u] = this->first[id_cycle];
 
      this->in_cycle[u] = true;
      this->cycle_id[u] = id_cycle;
      this->id_in_cycle[u] = cur_id;
      this->near_in_cycle[u] = u;
      this->id_near_cycle[u] = id_cycle;
      this->cycle_dist[u] = 0;
 
      u = nxt[u];
      cur_id++;
    }
  }

  int find_nxt(int u, vector<bool> &vis, vector<vector<int>> &adj) {
    for(int v: adj[u]) 
      if(!vis[v])
        return v;
    return -1;
  }
 
  // Time Complexity: O(V + E)
  void build(int n, int indexed_from, vector<int> &degree, vector<vector<int>> &adj) {
    queue<int> q;
    vector<bool> vis(n + indexed_from, false);
    vector<int> nxt(n + indexed_from);
    for(int i = indexed_from; i < n + indexed_from; i++) {
      if(adj[i].size() == 1) {
        q.push(i);
        vis[i] = true;
      }
    }
 
    vector<int> process_order;
    process_order.reserve(n + indexed_from);
    while(!q.empty()) {
      int u = q.front();
      q.pop();
 
      process_order.push_back(u);
 
      nxt[u] = find_nxt(u, vis, adj);
      if(--degree[nxt[u]] == 1) {
        q.push(nxt[u]);
        vis[nxt[u]] = true;
      }
    }
 
    int cycle_cnt = 0;
    for(int i = indexed_from; i < n + indexed_from; i++)
      if(!vis[i])
        compute_cycle(i, nxt, vis, adj);
 
    for(int i = (int)process_order.size() - 1; i >= 0; i--) {
      int u = process_order[i];
 
      this->near_in_cycle[u] = this->near_in_cycle[nxt[u]];
      this->id_near_cycle[u] = this->id_near_cycle[nxt[u]];
      this->cycle_dist[u] = this->cycle_dist[nxt[u]] + 1;
    }
  }
 
  void allocate(int n, int indexed_from) {
    this->cycle.resize(n + indexed_from);
    this->first.resize(n + indexed_from);
 
    this->in_cycle.resize(n + indexed_from, false);    
    this->cycle_id.resize(n + indexed_from, -1);
    this->id_in_cycle.resize(n + indexed_from, -1);    
    this->near_in_cycle.resize(n + indexed_from);    
    this->id_near_cycle.resize(n + indexed_from);    
    this->cycle_dist.resize(n + indexed_from);    
  }
 
 public:
  Functional_Graph(int n, int indexed_from, vector<int> degree, vector<vector<int>> &adj) {
    this->allocate(n, indexed_from);
    this->build(n, indexed_from, degree, adj);
  }
 
  // THE CYCLES ARE ALWAYS INDEXED BY ZERO!
 
  // number of cycles
  int cycle_cnt = 0;
  // Vertices present in the i-th cycle.
  vector<vector<int>> cycle;
  // first vertex of the i-th cycle
  vector<int> first;
 
  // The i-th vertex is present in any cycle?
  vector<bool> in_cycle;
  // id of the cycle that the vertex belongs. -1 if it doesn't belong to any cycle.
  vector<int> cycle_id;
  // Represents the id of the cycle of the i-th vertex. -1 if it doesn't belong to any cycle.
  vector<int> id_in_cycle;
  // Represents the id of the nearest vertex present in a cycle.
  vector<int> near_in_cycle;
  // Represents the id of the nearest cycle.
  vector<int> id_near_cycle;
  // Distance to the nearest cycle.
  vector<int> cycle_dist;
  // Represent the id of the component of the vertex.
  // Equal to id_near_cycle 
  vector<int> &comp = id_near_cycle;
};