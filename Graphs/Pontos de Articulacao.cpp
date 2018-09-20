// SE TIRAR TAIS VERTICES O GRAFO FICA DESCONEXO

vector<bool> ap(100000,false);
vector<int> low(100000,0), T(100000,0);
int tempo = 1;
list<int> adj[100000];

void artPoint(int u, int p) {

	low[u] = T[u] = tempo++;
	int children = 0;

	for(int v: adj[u]) {

	// cuidado com arestas paralelas
	// se tiver nao podemos fazer assim

	  if(T[v] == 0) {

			children++;
			artPoint(v,u);
			low[u] = min(low[v],low[u]);

		if(p == -1 && children > 1) {
			ap[u] = true;
		}

		if(p != -1 && low[v] > T[u])
			ap[u] = true;
	  } else if(v != p)
		  low[u] = min(low[u], T[v]);

	}
}

int main() {

	for(int i = 0; i < n; i++) 
		if(T[i] == 0)
			artPoint(i,-1);
}
