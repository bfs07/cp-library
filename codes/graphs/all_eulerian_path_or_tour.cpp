struct edge {
  int v, id;
  edge() {}
  edge(int v, int id) : v(v), id(id) {}
};

// The undirected + path and directed + tour wasn't tested in a problem.
// TEST AGAIN BEFORE SUBMITTING IT!
namespace graph {
// Namespace which auxiliary funcions are defined.
namespace detail {
pair<bool, pair<int, int>> check_both_directed(const vector<vector<edge>> &adj,
                                               const vector<int> &in_degree) {
  // source and destination
  int src = -1, dest = -1;
  // adj[i].size() represents the out degree of an vertex
  for (int i = 0; i < adj.size(); i++) {
    if ((int)adj[i].size() - in_degree[i] == 1) {
      if (src != -1)
        return make_pair(false, pair<int, int>());
      src = i;
    } else if ((int)adj[i].size() - in_degree[i] == -1) {
      if (dest != -1)
        return make_pair(false, pair<int, int>());
      dest = i;
    } else if (abs((int)adj[i].size() - in_degree[i]) > 1)
      return make_pair(false, pair<int, int>());
  }

  if (src == -1 && dest == -1)
    return make_pair(true, pair<int, int>(src, dest));
  else if (src != -1 && dest != -1)
    return make_pair(true, pair<int, int>(src, dest));

  return make_pair(false, pair<int, int>());
}

/// Builds the path/tour for directed graphs.
void build(const int u, vector<int> &tour, vector<vector<edge>> &adj,
           vector<bool> &used) {
  while (!adj[u].empty()) {
    const edge e = adj[u].back();
    if (!used[e.id]) {
      used[e.id] = true;
      adj[u].pop_back();
      build(e.v, tour, adj, used);
    } else
      adj[u].pop_back();
  }

  tour.push_back(u);
}

/// Auxiliary function to build the eulerian tour/path.
vector<int> set_build(vector<vector<edge>> &adj, const int E, const int first) {
  vector<int> path;
  vector<bool> used(E + 3);

  build(first, path, adj, used);

  for (int i = 0; i < adj.size(); i++)
    // if there are some remaining edges, it's not possible to build the tour.
    if (adj[i].size())
      return vector<int>();

  reverse(path.begin(), path.end());
  return path;
}
} // namespace detail

/// All vertices v should have in_degree[v] == out_degree[v]. It must not
/// contain a specific start and end vertices.
///
/// Time complexity: O(V * (log V) + E)
bool has_euler_tour_directed(const vector<vector<edge>> &adj,
                             const vector<int> &in_degree) {
  const pair<bool, pair<int, int>> aux =
      detail::check_both_directed(adj, in_degree);
  const bool valid = aux.first;
  const int src = aux.second.first;
  const int dest = aux.second.second;
  return (valid && src == -1 && dest == -1);
}

/// A directed graph has an eulerian path/tour if has:
/// - One vertex v such that out_degree[v] - in_degree[v] == 1
/// - One vertex v such that in_degree[v] - out_degree[v] == 1
/// - The remaining vertices v such that in_degree[v] == out_degree[v]
/// or
/// - All vertices v such that in_degree[v] - out_degree[v] == 0 -> TOUR
///
/// Returns a boolean value that indicates whether there's a path or not.
/// If there's a valid path it also returns two numbers: the source and the
/// destination. If the source and destination can be an arbitrary vertex it
/// will return the pair (-1, -1) for the source and destination (it means the
/// contains an eulerian tour).
///
/// Time complexity: O(V + E)
pair<bool, pair<int, int>>
has_euler_path_directed(const vector<vector<edge>> &adj,
                        const vector<int> &in_degree) {
  return detail::check_both_directed(adj, in_degree);
}

/// Returns the euler path. If the graph doesn't have an euler path it returns
/// an empty vector.
///
/// Time Complexity: O(V + E) for directed, O(V * log(V) + E) for undirected.
/// Time Complexity: O(adj.size() + sum(adj[i].size()))
vector<int> get_euler_path_directed(const int E, vector<vector<edge>> &adj,
                                    const vector<int> &in_degree) {
  const pair<bool, pair<int, int>> aux =
      has_euler_path_directed(adj, in_degree);
  const bool valid = aux.first;
  const int src = aux.second.first;
  const int dest = aux.second.second;

  if (!valid)
    return vector<int>();

  int first;
  if (src != -1)
    first = src;
  else {
    first = 0;
    while (adj[first].empty())
      first++;
  }

  return detail::set_build(adj, E, first);
}

/// Returns the euler tour. If the graph doesn't have an euler tour it returns
/// an empty vector.
///
/// Time Complexity: O(V + E)
/// Time Complexity: O(adj.size() + sum(adj[i].size()))
vector<int> get_euler_tour_directed(const int E, vector<vector<edge>> &adj,
                                    const vector<int> &in_degree) {
  const bool valid = has_euler_tour_directed(adj, in_degree);

  if (!valid)
    return vector<int>();

  int first = 0;
  while (adj[first].empty())
    first++;

  return detail::set_build(adj, E, first);
}

// The graph has a tour that passes to every edge exactly once and gets
// back to the first edge on the tour.
//
// A graph with an euler path has zero odd degree vertex.
//
// Time Complexity: O(V)
bool has_euler_tour_undirected(const vector<int> &degree) {
  for (int i = 0; i < degree.size(); i++)
    if (degree[i] & 1)
      return false;
  return true;
}

// The graph has a path that passes to every edge exactly once.
// It doesn't necessarely gets back to the beginning.
//
// A graph with an euler path has two or zero (tour) odd degree vertices.
//
// Returns a pair with the startpoint/endpoint of the path.
//
// Time Complexity: O(V)
pair<bool, pair<int, int>>
has_euler_path_undirected(const vector<int> &degree) {
  vector<int> odd_degree;
  for (int i = 0; i < degree.size(); i++)
    if (degree[i] & 1)
      odd_degree.pb(i);

  if (odd_degree.size() == 0)
    return make_pair(true, make_pair(-1, -1));
  else if (odd_degree.size() == 2)
    return make_pair(true, make_pair(odd_degree.front(), odd_degree.back()));
  else
    return make_pair(false, pair<int, int>());
}

vector<int> get_euler_tour_undirected(const int E, const vector<int> &degree,
                                      vector<vector<edge>> &adj) {
  if (!has_euler_tour_undirected(degree))
    return vector<int>();

  int first = 0;
  while (adj[first].empty())
    first++;

  return detail::set_build(adj, E, first);
}

/// Returns the euler tour. If the graph doesn't have an euler tour it returns
/// an empty vector.
///
/// Time Complexity: O(V + E)
/// Time Complexity: O(adj.size() + sum(adj[i].size()))
vector<int> get_euler_path_undirected(const int E, const vector<int> &degree,
                                      vector<vector<edge>> &adj) {
  auto aux = has_euler_path_undirected(degree);
  const bool valid = aux.first;
  const int x = aux.second.first;
  const int y = aux.second.second;

  if (!valid)
    return vector<int>();

  int first;
  if (x != -1) {
    first = x;
    adj[x].emplace_back(y, E + 1);
    adj[y].emplace_back(x, E + 1);
  } else {
    first = 0;
    while (adj[first].empty())
      first++;
  }

  vector<int> ans = detail::set_build(adj, E, first);
  reverse(ans.begin(), ans.end());
  if (x != -1)
    ans.pop_back();
  return ans;
}
}; // namespace graph