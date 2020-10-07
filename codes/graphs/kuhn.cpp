/// Created by viniciustht
struct Kuhn {
  vector<vector<int>> adj;
  vector<int> matchA, matchB, marcB;
  int n, m;
  bool matched = false;
  Kuhn(int n, int m) : n(n), m(m) {
    adj.resize(n, vector<int>());
    matchA.resize(n);
    matchB = marcB = vector<int>(m);
  }
  void add_edge(int u, int v) {
    adj[u].emplace_back(v);
    matched = false;
  }
  bool dfs(int u) {
    for (int &v : adj[u]) {
      if (marcB[v]) // || w > mid) // use with binary search
        continue;
      marcB[v] = 1;
      if (matchB[v] == -1 or dfs(matchB[v])) {
        matchB[v] = u;
        matchA[u] = v;
        return true;
      }
    }
    return false;
  }

  int matching() {
    memset(matchA.data(), -1, sizeof(int) * n);
    memset(matchB.data(), -1, sizeof(int) * m);
    // shuffle(adj.begin(), adj.end(), rng); // se o grafo pode ser esparso
    // for (auto v : adj)
    //   shuffle(v.begin(), v.end(), rng);
    int res = 0;
    bool aux = true;
    while (aux) {
      memset(marcB.data(), 0, sizeof(int) * m);
      aux = false;
      for (int i = 0; i < n; i++) {
        if (matchA[i] != -1)
          continue;
        if (dfs(i)) {
          res++;
          aux = true;
        }
      }
    }
    matched = true;
    return res;
  }
  void print_matching() {
    if (!matched)
      matching();
    for (int i = 0; i < n; i++)
      if (matchA[i] != -1)
        cerr << i + 1 << " " << matchA[i] + 1 << endl;
  }
};