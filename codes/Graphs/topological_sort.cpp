/// INDEXED BY ZERO 
///  
/// Time Complexity: O(n) 
vector<int> topological_sort(int n) {
  vector<int> in_degree(n, 0);

  for(int u = 0; u < n; u++)
    for(int v: adj[u])
      in_degree[v]++;

  queue<int> q;
  for(int i = 0; i < n; i++)
    if(in_degree[i] == 0) 
      q.push(i);
 
  int cnt = 0;
  vector<int> top_order;
  while(!q.empty()) {
    int u = q.front();
    q.pop();
    
    top_order.push_back(u); 
    cnt++;

    for(int v: adj[u])
      if(--in_degree[v] == 0)
        q.push(v); 
  }
 
  if(cnt != n) {
    cerr << "There exists a cycle in the graph" << endl;
    return vector<int>();
  } 

  return top_order;
}
