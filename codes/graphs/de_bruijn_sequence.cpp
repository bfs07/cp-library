// We can solve this problem by constructing a directed graph with
// k^(n-1) nodes with each node having k outgoing edges_order. Each node
// corresponds to a string of size n-1. Every edge corresponds to one of the k
// characters in A and adds that character to the starting string. For example,
// if n=3 and k=2, then we construct the following graph:

//            - 1 ->  (01)  - 1 ->
//           /         ^  |        \
// 0 -> (00)          1  0           (11) <- 1
//          \          |  v         /
//           <- 0 -   (10)  <- 0 -

// The node '01' is connected to node '11' through edge '1', as adding '1' to
// '01' (and removing the first character) gives us '11'.
//
// We can observe that every node in this graph has equal in-degree and
// out-degree, which means that a Eulerian circuit exists in this graph.

namespace graph {
namespace detail {
// Finding an valid eulerian path
void dfs(const string &node, const string &alphabet, set<string> &vis,
         string &edges_order) {
  for (char c : alphabet) {
    string nxt = node + c;
    if (vis.count(nxt))
      continue;

    vis.insert(nxt);
    nxt.erase(nxt.begin());
    dfs(nxt, alphabet, vis, edges_order);
    edges_order += c;
  }
}
}; // namespace detail

// Returns a string in which every string of the alphabet of size n appears in
// the resulting string exactly once.
//
// Time Complexity: O(alphabet.size() ^ n * log2(alphabet.size() ^ n))
string de_bruijn(const int n, const string &alphabet) {
  set<string> vis;
  string edges_order;

  string starting_node = string(n - 1, alphabet.front());
  detail::dfs(starting_node, alphabet, vis, edges_order);

  return edges_order + starting_node;
}
}; // namespace graph