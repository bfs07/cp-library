class DSU {

public:

  vector<int> root;
  vector<int> sz;

  DSU(int n) {
    this->root.resize(n + 1);
    iota(this->root.begin(), this->root.begin() + n + 1, 0);
    this->sz.resize(n + 1, 1);
  }

  int Find(int x) {
    if(this->root[x] == x)
      return x;
    return this->root[x] = this->Find(this->root[x]);
  }

  bool Union(int p, int q) {

    p = this->Find(p), q = this->Find(q);

    if(p == q)
      return false; 
    
    if(this->sz[p] > this->sz[q]) {
      this->root[q] = p;
      this->sz[p] += this->sz[q];
    } else {
      this->root[p] = q;
      this->sz[q] += this->sz[p];
    }

    return true;  
  }

};

struct edge {
  int u, v, w;
  edge() {}
  edge(int u, int v, int w) : u(u), v(v), w(w) {}

  bool operator<(const edge &a) const {
    return w < a.w;
  }
};

int kruskal(int n, vector<edge>& edges) {

  DSU dsu(n);

  sort(edges.begin(), edges.end());

  int weight = 0;
  for(int i = 0; i < (int)edges.size(); i++) {
    if(dsu.Union(edges[i].u, edges[i].v)) {
      weight += edges[i].w;
    }
  }

  // returns weight of mst
  return weight;
}