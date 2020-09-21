/// Code copied from: https://cp-algorithms.com/graph/min_cost_flow.html
struct Edge {
  const int from, to, cap, cost;
  Edge(const int from, const int to, const int cap, const int cost)
      : from(from), to(to), cap(cap), cost(cost) {}
};

const int INF = 1e9;
vector<vector<int>> adj, cost, cap;

/// Implementation of the SPFA algorithm.
void shortest_paths(const int n, const int src, vector<int> &d,
                    vector<int> &p) {
  d.assign(n, INF);
  d[src] = 0;
  vector<bool> inq(n, false);
  queue<int> q;
  q.emplace(src);
  p.assign(n, -1);

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    inq[u] = false;
    for (int v : adj[u]) {
      if (cap[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
        d[v] = d[u] + cost[u][v];
        p[v] = u;
        if (!inq[v]) {
          inq[v] = true;
          q.emplace(v);
        }
      }
    }
  }
}

/// Implementation of the min_cost_flow algorithm.
/// Returns a pair containing the maximum flow (less than or equal to k) and its
/// cost. Set K to INF in the parameter to find the minimum-cost maximum-flow.
///
/// Time Complexity: O(n²m²)
pair<int, int> min_cost_flow(const int N, const vector<Edge> &edges,
                             const int K, const int s, const int t) {
  adj.assign(N, vector<int>());
  cost.assign(N, vector<int>(N, 0));
  cap.assign(N, vector<int>(N, 0));
  for (const Edge &e : edges) {
    adj[e.from].emplace_back(e.to);
    adj[e.to].emplace_back(e.from);
    cost[e.from][e.to] = e.cost;
    cost[e.to][e.from] = -e.cost;
    cap[e.from][e.to] = e.cap;
  }

  int flow = 0, cost = 0;
  vector<int> d, p;
  while (flow < K) {
    shortest_paths(N, s, d, p);
    if (d[t] == INF)
      break;

    // find max flow on that path
    int f = K - flow;
    int cur = t;
    while (cur != s) {
      f = min(f, cap[p[cur]][cur]);
      cur = p[cur];
    }

    // apply flow
    flow += f;
    cost += f * d[t];
    cur = t;
    while (cur != s) {
      cap[p[cur]][cur] -= f;
      cap[cur][p[cur]] += f;
      cur = p[cur];
    }
  }

  return make_pair(flow, cost);
}
