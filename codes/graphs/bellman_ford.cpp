struct edge {
  int src, dest, weight;
  edge() {}
  edge(int src, int dest, int weight) : src(src), dest(dest), weight(weight) {}

  bool operator<(const edge &a) const { return weight < a.weight; }
};

/// Works to find the shortest path with negative edges.
/// Also detects cycles.
///
/// Time Complexity: O(n * e)
/// Space Complexity: O(n)
bool bellman_ford(vector<edge> &edges, int src, int n) {
  // n = qtd of vertices, E = qtd de arestas

  // To calculate the shortest path uncomment the line below
  // vector<int> dist(n, INF);

  // To check cycles uncomment the line below
  // vector<int> dist(n, 0);

  vector<int> pai(n, -1);
  int E = edges.size();

  dist[src] = 0;
  // Relax all edges n - 1 times.
  // A simple shortest path from src to any other vertex can have at-most n - 1
  // edges.
  for (int i = 1; i <= n - 1; i++) {
    for (int j = 0; j < E; j++) {
      int u = edges[j].src;
      int v = edges[j].dest;
      int weight = edges[j].weight;
      if (dist[u] != INF && dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        pai[v] = u;
      }
    }
  }

  // Check for NEGATIVE-WEIGHT CYCLES.
  // The above step guarantees shortest distances if graph doesn't contain
  // negative weight cycle. If we get a shorter path, then there is a cycle.
  bool is_cycle = false;
  int vert_in_cycle;
  for (int i = 0; i < E; i++) {
    int u = edges[i].src;
    int v = edges[i].dest;
    int weight = edges[i].weight;
    if (dist[u] != INF && dist[u] + weight < dist[v]) {
      is_cycle = true;
      pai[v] = u;
      vert_in_cycle = v;
    }
  }

  if (is_cycle) {
    for (int i = 0; i < n; i++)
      vert_in_cycle = pai[vert_in_cycle];

    vector<int> cycle;
    for (int v = vert_in_cycle; (v != vert_in_cycle || cycle.size() <= 1);
         v = pai[v])
      cycle.pb(v);

    reverse(cycle.begin(), cycle.end());

    for (int x : cycle) {
      cout << x + 1 << ' ';
    }
    cout << cycle.front() + 1 << endl;
    return true;
  } else
    return false;
}
