int rGraph[2000][2000];
int graph[2000][2000]; 
   
int V;
bool bfs(int s, int t, int parent[]) {
  bool visited[V];
  memset(visited, 0, sizeof(visited));

  // Create a queue, enqueue source vertex and mark source vertex
  // as visited
  queue <int> q;
  q.push(s);
  visited[s] = true;
  parent[s] = -1;

  // Standard BFS Loop
  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v=0; v<V; v++) {
      if (visited[v]==false && rGraph[u][v] > 0) {
        q.push(v);
        parent[v] = u;
        visited[v] = true;
      }
    }
  }
  // If we reached sink in BFS starting from source, then return true, else false
  return (visited[t] == true);
}

// Returns the maximum flow from s to t in the given graph
int fordFulkerson(int s, int t) {
  int u, v;
  // Create a residual graph and fill the residual graph with given capacities in the original graph as residual capacities in residual graph residual capacity of edge from i to j (if there is an edge. If rGraph[i][j] is 0, then there is not)  
  for (u = 0; u < V; u++)
    for (v = 0; v < V; v++)
      rGraph[u][v] = graph[u][v];

  int parent[V];  // This array is filled by BFS and to store path

  int max_flow = 0;// There is no flow initially

  // Augment the flow while tere is path from source to sink
  while (bfs(s, t, parent)) {
    // Find minimum residual capacity of the edges along the path filled by BFS. Or we can say find the maximum flow through the path found.
    int path_flow = INT_MAX;
    for (v=t; v!=s; v=parent[v]) {
      u = parent[v];
      path_flow = min(path_flow, rGraph[u][v]);
    }

    // update residual capacities of the edges and reverse edges
    // along the path
    for (v=t; v != s; v=parent[v]) {
      u = parent[v];
      rGraph[u][v] -= path_flow;
      rGraph[v][u] += path_flow;
    }

    // Add path flow to overall flow
    max_flow += path_flow;
  }

  // Return the overall flow
  return max_flow;
}

// PRINT THE FLOW AFTER RUNNING THE ALGORITHM
void print(int n) {
  for(int i = 1; i <= m; i++) {
    for(int j = m+1; j <= m*2; j++) {
	    cout << “flow from i(left) to j(right) is “ << graph[i][j] - rGraph[i][j] << endl;
    }
  }
}

void addEdge(int l, int r, int n, int x) {
	graph[l][r+n] = x;
}

void addEdgeSource(int l, int x) {
	graph[0][l] = x;
}

void addEdgeSink(int r, int n, int x) {
	graph[r+n][V-1] = x; 
}
