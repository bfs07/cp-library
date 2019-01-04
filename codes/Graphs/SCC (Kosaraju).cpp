int comp[312345];
vector<int> adj[312345];
// grafo reverso de adj
vector<int> trans[312345];
// contains each element of each component
vector<int> scc[312345];
int V;

void dfsTrans(int u, int id, int comp[]) {
  comp[u] = id;
  scc[id].push_back(u);
 
  for (int v: trans[u])
    if (!comp[v])
      dfsTrans(v, id, comp);
}
 
void getTranspose() {
  for (int u = 0; u < V; u++)
    for(int v: adj[u])
      trans[v].push_back(u);
}

void dfsFillOrder(int u, int comp[], stack<int> &Stack) {
  comp[u] = true;
 
  for(int v: adj[u])
    if(!comp[v])
      dfsFillOrder(v, comp, Stack);
 
  Stack.push(u);
}
 
// The main function that finds and prints all strongly connected 
// components
void computeSCC() {

  stack<int> Stack; 
  // Fill vertices in stack according to their finishing times
  for(int i = 0; i < V; i++)
    if(comp[i] == false)
      dfsFillOrder(i, comp, Stack);
 
  // Create a reversed graph
  getTranspose();
 
  memset(comp, 0, sizeof(comp));
 
  // Now process all vertices in order defined by Stack
  int id = 1;
  while(Stack.empty() == false) {
    int v = Stack.top();
    Stack.pop();
 
    if(comp[v] == false)
      dfsTrans(v, id++, comp);
  }
}

/* 
  ONLY WORKS WITH 0-INDEXED GRAPHS
  
  DONT FORGET TO DECLARE V
*/