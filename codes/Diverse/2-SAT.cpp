class SCC {
 private:
  // number of vertices
  int n;
  // indicates whether it is indexed from 0 or 1
  int indexed_from;
  // reversed graph
  vector<vector<int>> trans;

 private:
  void dfs_trans(int u, int id) {
    comp[u] = id;
    scc[id].push_back(u);
   
    for (int v: trans[u])
      if (comp[v] == -1)
        dfs_trans(v, id);
  }

  void get_transpose(vector<vector<int>>& adj) {
    for (int u = indexed_from; u < this->n + indexed_from; u++)
      for(int v: adj[u])
        trans[v].push_back(u);
  }

  void dfs_fill_order(int u, stack<int> &s, vector<vector<int>>& adj) {
    comp[u] = true;
   
    for(int v: adj[u])
      if(!comp[v])
        dfs_fill_order(v, s, adj);
   
    s.push(u);
  }

  // The main function that finds all SCCs
  void compute_SCC(vector<vector<int>>& adj) {

    stack<int> s; 
    // Fill vertices in stack according to their finishing times
    for(int i = indexed_from; i < this->n + indexed_from; i++)
      if(!comp[i])
        dfs_fill_order(i, s, adj);
   
    // Create a reversed graph
    get_transpose(adj);
   
    fill(comp.begin(), comp.end(), -1);
   
    // Now process all vertices in order defined by stack
    int id = 0;
    while(s.empty() == false) {
      int v = s.top();
      s.pop();
   
      if(comp[v] == -1)
        dfs_trans(v, id++);
    }
  }

 public:
  // number of the component of the i-th vertex
  // it's always indexed from 0
  vector<int> comp;
  // the i-th vector contains the vertices that belong to the i-th scc
  // it's always indexed from 0
  vector<vector<int>> scc;

  SCC(int n, int indexed_from, vector<vector<int>>& adj) {
    this->n = n;
    this->indexed_from = indexed_from;
    comp.resize(n + 1);
    trans.resize(n + 1);
    scc.resize(n + 1);

    this->compute_SCC(adj);
  }
};

// OBS: INDEXED FROM 0
class SAT_2 {

 private:
  vector<vector<int>> adj;
  int n;

 public:
  vector<bool> ans;

  SAT_2(int n) {
    this->n = n;
    adj.resize(2*n);
    ans.resize(n);
  }

  //  (X v Y)  = (X -> ¬Y) ∧ (¬X -> Y)
  void add_or(int x, bool pos_x, int y, bool pos_y) {
    assert(0 <= x < n);
    assert(0 <= y < n);
    adj[(x << 1) ^ pos_x].pb((y << 1) ^ (pos_y ^ 1));
    adj[(y << 1) ^ pos_y].pb((x << 1) ^ (pos_x ^ 1));
  }

  // (X xor Y) = (X v Y) ∧ (¬X v ¬Y) 
  // for this function the result is always 0 1 or 1 0 
  void add_xor(int x, bool pos_x, int y, bool pos_y) {
    assert(0 <= x < n);
    assert(0 <= y < n);
    add_or(x, y, pos_x, pos_y);
    add_or(x, y, pos_x^1, pos_y^1);
  }

  bool check(int n) {

    SCC scc(2*n, 0, adj);

    for(int i = 0; i < n; i++) {
      if(scc.comp[(i << 1) | 1] == scc.comp[(i << 1) | 0])
        return false;
      ans[i] = (scc.comp[(i << 1) | 1] < scc.comp[(i << 1) | 0]);
    }

    return true;
  }
};