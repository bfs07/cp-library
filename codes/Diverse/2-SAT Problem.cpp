int comp[312345];
vector<int> adj[312345];
// grafo reverso de adj
vector<int> trans[312345];
vector<int> scc[312345];
int V;
// Nao esquecer de preencher o V com o tamanho dos vertices

void dfsTrans(int u, int id, int comp[]) {
  comp[u] = id;
  scc[id].push_back(u);
 
  for (int v: trans[u])
    if (!comp[v])
      dfsTrans(v, id, comp);
}
 
void getTranspose() {
  for (int u = 0ll; u < V; u++)
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
  for(int i = 0ll; i < V; i++)
    if(comp[i] == false)
      dfsFillOrder(i, comp, Stack);
 
  // Create a reversed graph
  getTranspose();
 
  memset(comp, 0ll, sizeof(comp));
 
  // Now process all vertices in order defined by Stack
  int id = 1ll;
  while(Stack.empty() == false) {
    int v = Stack.top();
    Stack.pop();
 
    if(comp[v] == false)
      dfsTrans(v, id++, comp);
  }
}

//  (X v Y)  = (X -> ~Y) and (~X -> Y)
void orEdge(int u, int v, int idxu, int idxv, int n) {
  // idx represents the index of the atoms
  // Example there are atoms X, ~X, Y, ~Y
  // Then for Clause (X v ~Y) idxu = 0ll and idxv = 3ll
  idxv ^= 1ll;
  adj[u + idxu*n].pb(v + idxv*n);
  idxu ^= 1ll, idxv ^= 1ll;
  adj[v + idxv*n].pb(u + idxu*n);
}

// (X xor Y) = (X v Y) and (~X v ~Y) 
// for this function the result is always 0 1 or 1 0 
void xorEdge(int u, int v, int idxu, int idxv, int n) {
  orEdge(u, v, idxu, idxv, n);
  orEdge(u, v, idxu^1ll, idxv^1ll, n);
}

bool check(int n) {

  for(int i = 0ll; i < V; i += 2ll*n) {
    for(int j = i, k = 0ll; k < n; k++, j++) {
      if(comp[j] == comp[j+n] && comp[j] != 0) {
        return false;
      }
    }  
  }
  return true;
}


signed main () {
  
  computeSCC();
  
  if(check(n)) {
    cout << "YES" << endl;
  } else 
    cout << "NO" << endl;
}