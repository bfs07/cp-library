/// Requires DSU.cpp
struct edge {
  int u, v, w;
  edge() {}
  edge(int u, int v, int w) : u(u), v(v), w(w) {}

  bool operator<(const edge &a) const { return w < a.w; }
};

/// Returns weight of the minimum spanning tree of the graph.
///
/// Time Complexity: O(V log V)
int kruskal(int n, vector<edge> &edges) {
  DSU dsu(n);
  sort(edges.begin(), edges.end());

  int weight = 0;
  for (int i = 0; i < edges.size(); i++) {
    if (dsu.Union(edges[i].u, edges[i].v)) {
      weight += edges[i].w;
    }
  }

  return weight;
}