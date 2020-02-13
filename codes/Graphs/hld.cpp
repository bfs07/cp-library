class HLD {
 private:
  int n;
  // number of nodes below the i-th node
  vector<int> sz;

 private:
  int get_sz(const int u, const int p, const vector<vector<ii>> &adj) {
    this->sz[u] = 1;
    for(const ii &v: adj[u]) {
      if(v.ff == p)
        continue;
      this->sz[u] += this->get_sz(v.ff, u, adj);
    }
    return this->sz[u];
  }

  void dfs(const int u, const int id, const int p, const int w, const vector<vector<ii>> &adj) {

    this->weight[u] = w;
    this->chain_id[u] = id;
    this->id_in_chain[u] = chain_size[id];
    this->parent[u] = p;

    if(this->chain_head[id] == -1)
      this->chain_head[id] = u;
    this->chain_size[id]++;

    int maxx = -1, idx = -1, w_idx;
    for(const ii &v: adj[u]) {
      if(v.ff == p)
        continue;
      if(sz[v.ff] > maxx) {
        maxx = sz[v.ff];
        idx = v.ff;
        w_idx = v.ss;
      }
    }

    if(idx != -1)
      this->dfs(idx, id, u, w_idx, adj);

    for(const ii &v: adj[u]) {
      if(v.ff == idx || v.ff == p)
        continue;
      this->dfs(v.ff, this->number_of_chains++, u, v.ss, adj);
    }
  }

 public:
  HLD(const vector<vector<ii>> &adj) {
    this->n = adj.size();
    this->chain_head.resize(this->n + 1, -1);
    this->id_in_chain.resize(this->n + 1, -1);
    this->chain_id.resize(this->n + 1, -1);
    this->sz.resize(this->n + 1);
    this->chain_size.resize(this->n + 1);
    this->weight.resize(this->n + 1);
    this->parent.resize(this->n + 1);
    this->get_sz(1, -1, adj);
    this->dfs(1, 0, -1, -1, adj);
  }

 public:
  // the chains are indexed from 0
  int number_of_chains = 1;
  // topmost node of the chain
  vector<int> chain_head;
  // id of the i-th node in his chain
  vector<int> id_in_chain;
  // id of the chain that the i-th node belongs
  vector<int> chain_id;
  // size of the i-th chain
  vector<int> chain_size;
  // weight of the i-th vertex, the bottommost edge will store
  // the weight of the edge. The root has weight -1 
  vector<int> weight;
  // parent of the i-th node
  vector<int> parent;
};