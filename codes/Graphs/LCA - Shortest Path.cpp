// pra achar so o lca é so tirar o q ta comentado com (// short path)
int anc[105000][(int)log2(150000)+2];

vector<ii> adj[105000];
vector<int> level(105000), dist(105000), vis(105000,false);

void dfs(int u, int p, int d = 1) {

	level[u] = d;
	vis[u] = true; 

	for(ii x: adj[u]) {
		if(vis[x.ff])
			continue;
		dist[x.ff] = dist[u] + x.ss; // short path
		dfs(x.ff,u,d+1); 
	}
}

void init(int n) {

	for(int i = 0; i <= n; i++) {
		for(int j = 0; (1<<j) < n; j++) {
			anc[i][j] = -1;
		}
	}
  
}

void read(int n) {
  
  // ler a aresta i -> x com peso c
  for(int i = 1; i < n; i++) {
    int x,c;
    cin >> x >> c;    
    adj[x].pb(ii(i,c));
    adj[i].pb(ii(x,c));
    anc[i][0] = x;
  }
}

void build(int n) {
  
  dist[0] = 0; // short path
  dfs(0,-1);

  for(int j = 1; (1<<j) < n; j++) {
    for(int i = 0; i < n; i++) {
      if(anc[i][j-1] != -1)
        anc[i][j] = anc[anc[i][j-1]][j-1];
    }
  }

}

// Codigo para voltar k posicoes a partir de x 
int goBack(int x, int k)  {

  for(int i = 0; i < 32; i++) {
  	if(k & (1<<i))
  		x = anc[x][i];
  }
  return x;

}


int lca(int a, int b) {

  int ac = a, bc = b;
  // a esta mais embaixo na arvore
  if(level[b] > level[a])
    swap(a,b);

  int lg = log2(level[a]);

  // colocando a e b no msm nivel
  for(int i = lg; i >= 0; i--) {
    if(level[a]-(1<<i) >= level[b]) {
      a = anc[a][i];
    }
  }
  
  if(a == b) 
    // return a; // to find lca
    return dist[ac] + dist[bc] - 2*dist[a]; // short path

  // achando o filho do lca
  for(int i = lg; i >= 0; i--) {
    if(anc[a][i] != -1 && anc[a][i] != anc[b][i]) {
      a = anc[a][i];
      b = anc[b][i];
    }
  }
  // anc[a][0] é o LCA
  // return anc[a][0]; retorna o lca
  //cout << "LCA  = " << anc[a][0] << endl;
  return dist[ac] + dist[bc] - 2*dist[anc[a][0]];

}
