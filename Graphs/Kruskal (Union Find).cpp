struct edge {
	int u, v, w;
	edge() {}
	edge(int u, int v, int w) : u(u), v(v), w(w) {}
}

vector<edge> edges((int)2e6);
vector<int> root((int)2e6), sz((int)2e6);

int Find(int x) {
	if(root[x] == x)
		return x;
	return root[x] = Find(root[x]);
}

bool Union(int p, int q) {
	p = Find(p), q = Find(q);
	if(p == q)
		return false;	
	
	if(sz[p] > sz[q]) {
		root[q] = p;
		sz[p] += sz[q];
	} else {
		root[p] = q;
		sz[q] += sz[p];
	}
	return true;	
}

int kruskal(int n, int m) {

	iota(root.begin(), root.begin() + n + 1, 0);
	fill(sz.begin(), sz.begin()+n  + 1, 1);

	int c = 0;
	for(int i = 0; i < (int)edges.size(); i++) {
		if(Union(edges[i].u, edges[i].v)) {
			c += edges[i].w;
		}
	}

	// returns weight of mst
	return c;
} 
