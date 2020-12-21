// Remove comments to add rollback
class DSU {
public:
  vector<int> root, sz;
  // stack<tuple<int, int, int>> old_root, old_sz;

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
    // DONT USE PATH COMPRESSION WITH ROLLBACK!!
    // return Find(root[x]);
  }

  /// Unites two sets in which u and v belong.
  /// Returns false if they already belong to the same set.
  ///
  /// Time Complexity: O(1)
  bool Union(int u, int v /* , int idx */) {
    u = Find(u), v = Find(v);
    if (u == v)
      return false;

    if (sz[u] < sz[v])
      swap(u, v);

    // old_root.emplace(idx, v, root[v]);
    // old_sz.emplace(idx, u, sz[u]);
    root[v] = u;
    sz[u] += sz[v];
    return true;
  }

  // void rollback() {
  //   int idx, u, val;
  //   tie(idx, u, val) = old_root.top();
  //   old_root.pop();
  //   root[u] = val;
  //   tie(idx, u, val) = old_sz.top();
  //   old_sz.pop();
  //   sz[u] = val;
  // }
};