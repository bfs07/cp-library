class HLD {
private:
  int n;
  // number of nodes below the i-th node
  vector<int> sz;

private:
  void allocate() {
    // this->id_in_tree.resize(this->n + 1, -1);
    this->chain_head.resize(this->n + 1, -1);
    this->chain_id.resize(this->n + 1, -1);
    this->sz.resize(this->n + 1);
    this->parent.resize(this->n + 1, -1);
    // this->id_in_chain.resize(this->n + 1, -1);
    // this->chain_size.resize(this->n + 1);
  }

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
           const vector<vector<int>> &adj, int &nidx) {
    // this->id_in_tree[u] = nidx++;
    this->chain_id[u] = id;
    // this->id_in_chain[u] = chain_size[id]++;
    this->parent[u] = p;

    if (this->chain_head[id] == -1)
      this->chain_head[id] = u;

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
      this->dfs(idx, id, u, adj, nidx);

    for (const int v : adj[u]) {
      if (v == idx || v == p)
        continue;
      this->dfs(v, this->number_of_chains++, u, adj, nidx);
    }
  }

  void build(const int root_idx, const vector<vector<int>> &adj) {
    this->get_sz(root_idx, -1, adj);
    int nidx = 0;
    this->dfs(root_idx, 0, -1, adj, nidx);
  }

  // int _compute(const int u, const int limit, Seg_Tree &st) {
  //   int ans = 0, v;
  //   for (v = u; chain_id[v] != chain_id[limit];
  //        v = parent[chain_head[chain_id[v]]]) {
  //     // change below
  //     ans = max(ans, st.query(id_in_tree[chain_head[chain_id[v]]],
  //                    id_in_tree[v]));
  //   }
  //   ans = max(ans, st.query(id_in_tree[limit], id_in_tree[v]));
  //   return ans;
  // }

public:
  /// Builds the chains.
  ///
  /// Time Complexity: O(n)
  HLD(const int root_idx, const vector<vector<int>> &adj) : n(adj.size()) {
    allocate();
    build(root_idx, adj);
  }

  /// Computes the paths until a limit using segment tree.
  /// Uncomment id_in_tree!!!
  ///
  /// Time Complexity: O(log^2(n))
  // int compute(const int u, const int limit, Seg_Tree &st) {
  //   return _compute(u, limit, st);
  // }

  // TAKE CARE, YOU MAY GET MLE!!!
  // the chains are indexed from 0
  int number_of_chains = 1;
  // topmost node of the chain
  vector<int> chain_head;
  // id of the node based on the order of the dfs (indexed by 0)
  // vector<int> id_in_tree;
  // id of the i-th node in his chain
  // vector<int> id_in_chain;
  // id of the chain that the i-th node belongs
  vector<int> chain_id;
  // size of the i-th chain
  // vector<int> chain_size;
  // parent of the i-th node, -1 for root
  vector<int> parent;
};