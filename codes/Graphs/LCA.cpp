// in order to find the lca vertex remove comments (// short path)
// INDEXED FROM 0

class LCA
{

public:

  // using ii = pair<int, int>;

  // matrix to store the ancestors of each node in power of 2 levels
  vector<vector<int>> anc;
  vector<vector<int>> cost; // max-min cost
  vector<int> level;
  // distance from root
  vector<int> dist; 
  vector<bool> vis;
  // INDEXED from 0 or 1??
  int start_idx;

  explicit LCA(int start_idx, int n, vector<vector<ii>> &adj)
  {
    // initializes a matrix [n][lg n] with -1
    this->anc.resize(n + 1, vector<int>((int)log2(n) + 1, -1));
    // this->cost.resize(n + 1, vector<int>((int)log2(n) + 1, -1)); // max-min cost
    this->level.resize(n + 1, -1);
    // this->dist.resize(n + 1); // short path
    this->vis.resize(n + 1, false);
    this->start_idx = start_idx;
    this->build(adj);
  }

  int lca(int a, int b)
  {
    int a_cpy = a, b_cpy = b;
    // a is below b
    if(this->level[b] > this->level[a])
      swap(a,b);

    int lg = log2(this->level[a]);

    // checking whether a and b are in the same level
    for(int i = lg; i >= 0; i--)
    {
      if(this->level[a]-(1<<i) >= this->level[b])
      {
        a = this->anc[a][i];
      }
    }

    if(a == b) 
      return a; // to find lca
      // return this->dist[a_cpy] + this->dist[b_cpy] - 2*this->dist[a]; // short path

    for(int i = lg; i >= 0; i--)
    {
      if(this->anc[a][i] != -1 && this->anc[a][i] != this->anc[b][i])
      {
        a = this->anc[a][i];
        b = this->anc[b][i];
      }
    }

    // anc[a][0] is the LCA
    return anc[a][0]; // returns the LCS
    //cout << "LCA  = " << anc[a][0] << endl;
    // returns the shortest path from a to b
    // return this->dist[a_cpy] + this->dist[b_cpy] - 2*this->dist[anc[a][0]];

  }

  int max_edge(int v, int p) {

    if(this->level[v] < this->level[p])
      swap(v, p);

    int k = this->level[v] - this->level[p];
    int ans = -1;

    for(int i = 0; k > 0; i++, k >>= 1) 
    {
      if(k & 1) 
      {
        v = this->anc[v][i];
        // ans = max(ans, this->cost[v][i]);
      }
    }

    return ans;
  }

  // go up k levels from x
  int go_back(int x, int k) 
  {
    for(int i = 0; k > 0; i++, k >> 1) 
    {
      if(k & 1) 
      {
        x = this->anc[x][i];
      }
    }
    return x;

  }

private:

  void build(vector<vector<ii>> &adj)
  {
    // dist[this->start_idx] = 0; // short path
    dfs_LCA(this->start_idx, -1, 1, -1, adj);

    for(int j = 1; j < anc.front().size(); j++)
    {
      for(int i = 0; i < anc.size(); i++)
      {
        if(this->anc[i][j-1] != -1) 
        {
          this->anc[i][j] = this->anc[this->anc[i][j-1]][j-1];
          // this->cost[i][j] = max(this->cost[i][j-1], this->cost[anc[i][j-1]][j-1]); // max-min cost
        }
      }
    }

  }

  void dfs_LCA(const int u, const int p, const int d, const int w, vector<vector<ii>> &adj) 
  {
    this->level[u] = d;
    this->vis[u] = true; 
    this->anc[u][0] = p;
    // this->cost[u][0] = w; // max-min cost

    for(ii &x: adj[u])
    {
      if(this->vis[x.ff])
        continue;
      // this->dist[x.ff] = this->dist[u] + x.ss; // short path
      // dfs_LCA(x.ff, u, d+1, x.ss, adj); // max-min cost
    }
  }

};