class HLD {
private:
  int n;
  // number of nodes below the i-th node
  vector<int> sz;

private:
  int get_sz(const int u, const int p, const vector<vector<int>> &adj) {
    this->sz[u] = 1;
    for (const int v : adj[u]) {
      if (v == p)
        continue;
      this->sz[u] += this->get_sz(v, u, adj);
    }
    return this->sz[u];
  }

  void dfs(const int u, const int id, const int p,
           const vector<vector<int>> &adj) {
    this->chain_id[u] = id;
    this->id_in_chain[u] = chain_size[id];
    this->parent[u] = p;

    if (this->chain_head[id] == -1)
      this->chain_head[id] = u;
    this->chain_size[id]++;

    int maxx = -1, idx = -1;
    for (const int v : adj[u]) {
      if (v == p)
        continue;
      if (sz[v] > maxx) {
        maxx = sz[v];
        idx = v;
      }
    }

    if (idx != -1)
      this->dfs(idx, id, u, adj);

    for (const int v : adj[u]) {
      if (v == idx || v == p)
        continue;
      this->dfs(v, this->number_of_chains++, u, adj);
    }
  }

public:
  /// Builds the chains.
  ///
  /// Time Complexity: O(n)
  HLD(const int root_idx, const vector<vector<int>> &adj) {
    this->n = adj.size();
    this->chain_head.resize(this->n + 1, -1);
    this->id_in_chain.resize(this->n + 1, -1);
    this->chain_id.resize(this->n + 1, -1);
    this->sz.resize(this->n + 1);
    this->chain_size.resize(this->n + 1);
    this->parent.resize(this->n + 1, -1);
    this->get_sz(root_idx, -1, adj);
    this->dfs(root_idx, 0, -1, adj);
  }

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
  // parent of the i-th node, -1 for root
  vector<int> parent;
};