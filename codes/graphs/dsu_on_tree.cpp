/// Problem: What's the level of the subtree of u which contains the most number
/// of nodes? In case of tie, choose the level with small number.

vector<int> sub_sz(const int root_idx, const vector<vector<int>> &adj) {
  vector<int> sub(adj.size());
  function<int(int, int)> dfs = [&](const int u, const int p) {
    sub[u] = 1;
    for (int v : adj[u])
      if (v != p)
        sub[u] += dfs(v, u);
    return sub[u];
  };
  dfs(root_idx, -1);
  return sub;
}

vector<int> sz;
int dep[MAXN];
vector<vector<int>> adj(MAXN);
int maxx, ans;
void add(int u, int p, int l, int big_child, int val) {
  dep[l] += val;
  if (dep[l] > maxx || (dep[l] == maxx && l < ans)) {
    ans = l;
    maxx = dep[l];
  }
  for (int v : adj[u]) {
    if (v == p || big_child == v)
      continue;
    add(v, u, l + 1, big_child, val);
  }
}

vector<int> q(MAXN);
void dfs(int u, int p, int l, bool keep) {
  int idx = -1, val = -1;
  for (int v : adj[u]) {
    if (v == p)
      continue;
    if (sz[v] > val) {
      val = sz[v];
      idx = v;
    }
  }
  // idx now contains the index of the node of the biggest subtree
  for (int v : adj[u]) {
    if (v == p || v == idx)
      continue;
    // precalculate the answer for small subtrees
    dfs(v, u, l + 1, 0);
  }

  if (idx != -1) {
    // precalculate the answer for the biggest subtree and keep the results
    dfs(idx, u, l + 1, 1);
  }

  // Change below to apply the bruteforce you need. GENERALLY YOU SHOULD ONLY
  // MODIFY BELOW. 
  // bruteforce all subtrees other than idx
  add(u, p, l, idx, 1);

  // the answer of u is the level ans. As it is relative to the input tree we
  // need to subtract it to the current level of u
  q[u] = ans - l;
  if (keep == 0) {
    // removing the calculated answer for the subtree, if it doesn't belong to
    // the biggest subtree of it's parent (keep = 0)
    add(u, p, l, -1, -1);
    // clearing the answer
    maxx = 0, ans = 0;
  }
}

/// MODIFY TO WORK WITH DISCONNECTED GRAPHS!!!
///
/// Time Complexity: O(n log n)
void precalculate() {
  sz = sub_sz(1, adj);
  dfs(1, -1, 0, 0);
}