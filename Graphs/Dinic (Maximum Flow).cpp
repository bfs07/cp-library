const int MAXVERT = 3010;
const int MAXEDGES = 200000;

int adj[MAXVERT], to[MAXEDGES], ant[MAXEDGES], wt[MAXEDGES], z, n;
// wt = weight
int copy_adj[MAXVERT], fila[MAXVERT], level[MAXVERT];
int wtReal[MAXEDGES], V;
int aux[MAXEDGES];	

void clear() {
	memset(adj, -1, sizeof(adj));
	z = 0;
}

// coloca a i-ésima aresta criada num vetor
// a i-ésima aresta é colocada na posição 2*i dois vetores to,ant,wt
void add(int u, int v, int k) {
	to[z] = v;
	ant[z] = adj[u];
	wt[z] = k;
	adj[u] = z++;
	swap(u, v);
	to[z] = v;
	ant[z] = adj[u];
	wt[z] = 0;
	adj[u] = z++;
}

void addToSource(int l, int k) {
	add(0, l, k);
}

void addToSink(int r, int k) {
	add(r, V-1, k);
}

int bfs(int source, int sink) {
	memset(level, -1, sizeof(level));
	level[source] = 0;
	int front = 0, size = 0, v;
	fila[size++] = source;
	while(front < size) {
		v = fila[front++];
		for(int i = adj[v]; i != -1; i = ant[i]) {
			if(wt[i] && level[to[i]] == -1) {
				level[to[i]] = level[v] + 1;
				fila[size++] = to[i];
			}
		}
	}
	return level[sink] != -1;
}

int dfs(int v, int sink, int flow) {
	if(v == sink) return flow;
	int f;
	for(int &i = copy_adj[v]; i != -1; i = ant[i]) {
		if(wt[i] && level[to[i]] == level[v] + 1 && (f = dfs(to[i], sink, min(flow, wt[i])))) {
			wt[i] -= f;
			wt[i ^ 1] += f;
			return f;
		}
	}
	return 0;
}

int maxflow() {
	int ret = 0, flow;
	int source = 0, sink = V-1;
	while(bfs(source, sink)) {
		memcpy(copy_adj, adj, sizeof(adj));
		while((flow = dfs(source, sink, 1 << 30))) {
			ret += flow;
		}
	}

	// apos a execução do algoritmo wt estara modificado
	return ret;
}

void print() {

	int mat[V+1][V+1];
	memset(mat, 0, sizeof(mat));
	for(int i = 0; i < z; i+= 2) {
		mat[to[i+1]][to[i]] = wt[i+1];
	}

	for(int i = 0; i < V; i++) {
		for(int j = 0; j < V; j++) {
			cout << mat[i][j] << ' ';
		}
		cout << endl;
	}
}