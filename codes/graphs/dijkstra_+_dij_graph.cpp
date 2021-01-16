/// Works also with 1-indexed graphs.
class Dijkstra {
private:
  static constexpr int INF = 2e18;
  bool CREATE_GRAPH = false;
  int src;
  int n;
  vector<int> _dist;
  vector<vector<int>> parent;

private:
  /// Time Complexity: O(E log V)
  void _compute(const int src, const vector<vector<pair<int, int>>> &adj) {
    _dist.resize(this->n, INF);
    vector<bool> vis(this->n, false);

    if (CREATE_GRAPH) {
      parent.resize(this->n);

      for (int i = 0; i < this->n; i++)
        parent[i].emplace_back(i);
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        pq;
    pq.emplace(0, src);
    _dist[src] = 0;

    while (!pq.empty()) {
      int u = pq.top().second;
      pq.pop();
      if (vis[u])
        continue;
      vis[u] = true;

      for (const pair<int, int> &x : adj[u]) {
        int v = x.first, w = x.second;

        if (_dist[u] + w < _dist[v]) {
          _dist[v] = _dist[u] + w;
          pq.emplace(_dist[v], v);
          if (CREATE_GRAPH) {
            parent[v].clear();
            parent[v].emplace_back(u);
          }
        } else if (CREATE_GRAPH && _dist[u] + w == _dist[v]) {
          parent[v].emplace_back(u);
        }
      }
    }
  }

  vector<vector<int>> gen_dij_graph(const int dest) {
    vector<vector<int>> dijkstra_graph(this->n);
    vector<bool> vis(this->n, false);
    queue<int> q;

    q.emplace(dest);
    while (!q.empty()) {
      int v = q.front();
      q.pop();

      for (const int u : parent[v]) {
        if (u == v)
          continue;
        dijkstra_graph[u].emplace_back(v);
        if (!vis[u]) {
          q.emplace(u);
          vis[u] = true;
        }
      }
    }
    return dijkstra_graph;
  }

  vector<int> gen_min_path(const int dest) {
    vector<int> path, prev(this->n, -1), d(this->n, INF);
    queue<int> q;

    q.emplace(dest);
    d[dest] = 0;

    while (!q.empty()) {
      int v = q.front();
      q.pop();

      for (const int u : parent[v]) {
        if (u == v)
          continue;
        if (d[v] + 1 < d[u]) {
          d[u] = d[v] + 1;
          prev[u] = v;
          q.emplace(u);
        }
      }
    }

    int cur = this->src;
    while (cur != -1) {
      path.emplace_back(cur);
      cur = prev[cur];
    }

    return path;
  }

public:
  /// Allows creation of dijkstra graph and getting the minimum path.
  Dijkstra(const int src, const bool create_graph,
           const vector<vector<pair<int, int>>> &adj)
      : n(adj.size()), src(src), CREATE_GRAPH(create_graph) {
    this->_compute(src, adj);
  }

  /// Constructor that computes only the Dijkstra minimum path from src.
  ///
  /// Time Complexity: O(E log V)
  Dijkstra(const int src, const vector<vector<pair<int, int>>> &adj)
      : n(adj.size()), src(src) {
    this->_compute(src, adj);
  }

  /// Returns the Dijkstra graph of the graph.
  ///
  /// Time Complexity: O(V)
  vector<vector<int>> dij_graph(const int dest) {
    assert(CREATE_GRAPH);
    return gen_dij_graph(dest);
  }

  /// Returns the vertices present in a path from src to dest with
  /// minimum cost and a minimum length.
  ///
  /// Time Complexity: O(V)
  vector<int> min_path(const int dest) {
    assert(CREATE_GRAPH);
    return gen_min_path(dest);
  }

  /// Returns the distance from src to dest.
  int dist(const int dest) {
    assert(0 <= dest), assert(dest < n);
    return _dist[dest];
  }
};