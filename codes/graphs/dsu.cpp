class DSU {
  vector<int> root, sz;

public:
  DSU(const int n) {
    root.resize(n + 1);
    iota(root.begin(), root.begin() + n + 1, 0ll);
    sz.resize(n + 1, 1);
  }

  /// Returns the id of the set in which the element x belongs.
  ///
  /// Time Complexity: O(1)
  int Find(const int x) {
    if (root[x] == x)
      return x;
    return root[x] = Find(root[x]);
  }

  /// Unites two sets in which p and q belong.
  /// Returns false if they already belong to the same set.
  ///
  /// Time Complexity: O(1)
  bool Union(int p, int q) {
    p = Find(p), q = Find(q);
    if (p == q)
      return false;

    if (sz[p] < sz[q])
      swap(p, q);

    root[q] = p;
    sz[p] += sz[q];
    return true;
  }
};