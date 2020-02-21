
struct edge {
  int u, v, w;
  edge() {}
  edge(int u, int v, int w) : u(u), v(v), w(w) {}

  bool operator<(const edge &a) const {
    return w < a.w;
  }
};

void BellmanFord(vector<edge> edges,int src, int V, int E)  {
  // V = qtd of vertices, E = qtd de arestas
  int dist[V];

  // Step 1: Initialize distances from src to all other vertices
  // as INFINITE
  for (int i = 0; i < V; i++)
    dist[i] = INF;
  dist[src] = 0;
  // Step 2: Relax all edges |V| - 1 times. A simple shortest path from src to any other vertex can have at-most |V| - 1 edges
  for (int i = 1; i <= V-1; i++) {
    for (int j = 0; j < E; j++) {
      int u = edges[j].src;
      int v = edges[j].dest;
      int weight = edges[j].weight;
      if (dist[u] != INF && dist[u] + weight < dist[v])
        dist[v] = dist[u] + weight;
    }
  }
  // Step 3: check for NEGATIVE-WEIGHT CYCLES.  The above step guarantees shortest distances if graph doesn't contain negative weight cycle.  If we get a shorter path, then there is a cycle.
  for (int i = 0; i < E; i++) {
    int u = edges[i].src;
    int v = edges[i].dest;
    int weight = edges[i].weight;
    if (dist[u] != INF && dist[u] + weight < dist[v])
      printf("Graph contains negative weight cycle");
  }
  printArr(dist, V);
}
