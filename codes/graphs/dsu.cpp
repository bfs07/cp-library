class DSU {
public:
  vector<int> root;
  vector<int> sz;

  DSU(int n) {
    this->root.resize(n + 1);
    iota(this->root.begin(), this->root.begin() + n + 1, 0ll);
    this->sz.resize(n + 1, 1);
  }

  int Find(int x) {
    if (this->root[x] == x)
      return x;
    return this->root[x] = this->Find(this->root[x]);
  }

  bool Union(int p, int q) {
    p = this->Find(p), q = this->Find(q);

    if (p == q)
      return false;

    if (this->sz[p] > this->sz[q]) {
      this->root[q] = p;
      this->sz[p] += this->sz[q];
    } else {
      this->root[p] = q;
      this->sz[q] += this->sz[p];
    }

    return true;
  }
};