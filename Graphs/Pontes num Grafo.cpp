//SE TIRA-LAS O GRAFO FICA DESCONEXO
// OBS: PRESTAR ATENCAO EM SELF-LOOPS, É MELHOR NÃO ADICIONA-LOS
// SO FUNCIONA EM GRAFO NÃO DIRECIONADO
float t=1;
vector<int> T(INF,0); //Tempo necessário para chegar naquele vértice na dfs 
vector<int> adj[INF]; 
vector<int> Low(INF); // Tempo “mínimo” para chegar naquele vértice na dfs
vector<int> ciclo(INF, false);
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
		    cout << u << v << endl;
			// ponte de u para v
		  }
		}
		else
		  Low[u]=min(Low[u], T[v]);
		ciclo[u] |= (T[u]>=Low[v]);
		//checa se o vértice u faz    //parte de um ciclo
	}
}
