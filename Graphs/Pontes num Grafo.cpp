//SE TIRA-LAS O GRAFO FICA DESCONEXO
// OBS: PRESTAR ATENCAO EM SELF-LOOPS, É MELHOR NÃO ADICIONA-LOS
// SO FUNCIONA EM GRAFO NÃO DIRECIONADO
int t=1;
vector<int> T((int)2e6,0); //Tempo necessário para chegar naquele vértice na dfs 
vector<int> adj[(int)2e6]; 
vector<int> Low((int)2e6); // Tempo “mínimo” para chegar naquele vértice na dfs
vector<int> ciclo((int)2e6, false);
vector<ii> bridges;
void dfs(int u, int p){
	Low[u] = T[u] = t;
	t++;
	for(auto v : adj[u]){
		if(v==p){
		  //checa arestas paralelas
			p=-1;
			continue;
		}
		//se ele ainda não foi visited
		else if(T[v]==0){
		  dfs(v,u);
		  Low[u]=min(Low[u], Low[v]);
		  if(Low[v]>T[u]) {
		    bridges.pb(ii(min(u,v), (max(u,v))));
			// ponte de u para v
		  }
		}
		else
		  Low[u]=min(Low[u], T[v]);
		ciclo[u] |= (T[u]>=Low[v]);
		//checa se o vértice u faz    //parte de um ciclo
	}
}

void clear() {

	for(int i = 0; i <= n; i++) {
		T[i] = 0, Low[i] = 0, adj[i].clear(), ciclo[i] = false;
	}
	bridges.clear();

}

signed main () {
	
	for(int i = 0; i < n; i++) 
		if(T[i] == 0)
			dfs(i, -1);

	sort(bridges.begin(), bridges.end());

	cout << (int)bridges.size() << endl;
	for(int i = 0; i < bridges.size(); i++) {
		cout << bridges[i].ff << " - " << bridges[i].ss << endl;
	}
	cout << endl;

	clear();

}
