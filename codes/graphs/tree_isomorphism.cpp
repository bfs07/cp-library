/// THE VALUES OF THE VERTICES MUST BELONG FROM 1 TO N.
namespace tree {
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

vector<uint64_t> base;
uint64_t build(const int u, const int p, const vector<vector<int>> &adj,
               const int level = 0) {
  if (level == base.size())
    base.emplace_back(rng());
  uint64_t hsh = 1;
  vector<uint64_t> child;
  for (const int v : adj[u])
    if (v != p)
      child.emplace_back(build(v, u, adj, level + 1));
  sort(child.begin(), child.end());
  for (const uint64_t x : child)
    hsh = hsh * base[level] + x;
  return hsh;
}

/// Returns whether two rooted trees are isomorphic or not.
///
/// Time Complexity: O(n)
bool same(const int root_1, const vector<vector<int>> &adj1, const int root_2,
          const vector<vector<int>> &adj2) {
  if (adj1.size() != adj2.size())
    return false;
  return build(root_1, -1, adj1) == build(root_2, -1, adj2);
}

/// Returns whether two non-rooted trees are isomorphic or not.
/// REQUIRES centroid.cpp!!!
///
/// Time Complexity: O(n)
bool same(const int n, const int indexed_from, const vector<vector<int>> &adj1,
          const vector<vector<int>> &adj2) {
  vector<int> c1 = centroid(n, indexed_from, adj1),
              c2 = centroid(n, indexed_from, adj2);
  for (const int v : c2)
    if (same(c1.front(), adj1, v, adj2))
      return true;
  return false;
}
} // namespace tree