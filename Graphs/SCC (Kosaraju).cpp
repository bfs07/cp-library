bool vis[312345];
vector<int> adj[312345];
// grafo reverso de adj
vector<int> trans[312345];
vector<int> scc[312345];
int V;

void dfsTrans(int u, int id, bool vis[]) {
  vis[u] = true;
  scc[id].push_back(u);
 
  for (int v: trans[u])
    if (!vis[v])
      dfsTrans(v, id, vis);
}
 
void getTranspose() {
  for (int u = 0; u < V; u++)
    for(int v: adj[u])
      trans[v].push_back(u);
}

void dfsFillOrder(int u, bool vis[], stack<int> &Stack) {
  vis[u] = true;
 
  for(int v: adj[u])
    if(!vis[v])
      dfsFillOrder(v, vis, Stack);
 
  Stack.push(u);
}
 
// The main function that finds and prints all strongly connected 
// components
void computeSCC() {

  stack<int> Stack; 
  // Fill vertices in stack according to their finishing times
  for(int i = 0; i < V; i++)
    if(vis[i] == false)
      dfsFillOrder(i, vis, Stack);
 
  // Create a reversed graph
  getTranspose();
 
  memset(vis, 0, sizeof(vis));
 
  // Now process all vertices in order defined by Stack
  int id = 0;
  while(Stack.empty() == false) {
    int v = Stack.top();
    Stack.pop();
 
    if(vis[v] == false)
      dfsTrans(v, id++, vis);
  }
}