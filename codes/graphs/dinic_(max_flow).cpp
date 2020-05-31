// Created by Ubiratan Neto

struct Dinic {

  struct FlowEdge {
    int v, rev, c, cap;
    bool is_rev;
    FlowEdge() {}
    FlowEdge(int v, int c, int cap, int rev, bool is_rev)
        : v(v), c(c), cap(cap), rev(rev), is_rev(is_rev) {}
  };

  vector<vector<FlowEdge>> adj;
  vector<int> level, used;
  int src, snk, V;
  int sz;
  int max_flow;
  bool calculated;
  Dinic() {}
  Dinic(int n) {
    calculated = false;
    src = 0;
    snk = n + 1;
    adj.resize(n + 2, vector<FlowEdge>());
    level.resize(n + 2);
    used.resize(n + 2);
    sz = n + 2;
    V = n + 2;
    max_flow = 0;
  }

  void add_edge(int u, int v, int c) {
    int id1 = adj[u].size();
    int id2 = adj[v].size();
    adj[u].emplace_back(FlowEdge(v, c, c, id2, false));
    adj[v].emplace_back(FlowEdge(u, 0, 0, id1, true));
  }

  void add_to_src(int v, int c) {
    adj[src].emplace_back(FlowEdge(v, c, c, -1, false));
  }

  void add_to_snk(int u, int c) {
    adj[u].emplace_back(FlowEdge(snk, c, c, -1, false));
  }

  bool bfs() {
    for (int i = 0; i < sz; i++) {
      level[i] = -1;
    }

    level[src] = 0;
    queue<int> q;
    q.push(src);

    while (!q.empty()) {
      int cur = q.front();
      q.pop();
      for (FlowEdge e : adj[cur]) {
        if (level[e.v] == -1 && e.c > 0) {
          level[e.v] = level[cur] + 1;
          q.push(e.v);
        }
      }
    }

    return (level[snk] == -1 ? false : true);
  }

  int send_flow(int u, int flow) {
    if (u == snk)
      return flow;

    for (int &i = used[u]; i < adj[u].size(); i++) {
      FlowEdge &e = adj[u][i];

      if (level[u] + 1 != level[e.v] || e.c <= 0)
        continue;

      int new_flow = min(flow, e.c);
      int adjusted_flow = send_flow(e.v, new_flow);

      if (adjusted_flow > 0) {
        e.c -= adjusted_flow;
        if (e.rev != -1)
          adj[e.v][e.rev].c += adjusted_flow;
        return adjusted_flow;
      }
    }

    return 0;
  }

  int calculate() {
    if (src == snk) {
      max_flow = -1;
      return -1;
    } // not sure if needed

    max_flow = 0;

    while (bfs()) {
      for (int i = 0; i < sz; i++)
        used[i] = 0;
      while (int inc = send_flow(src, INF))
        max_flow += inc;
    }
    calculated = true;

    return max_flow;
  }

  vector<pair<int, int>> mincut(vector<vector<int>> &mat_adj) {
    assert(calculated);
    int mat[sz][sz];
    memset(mat, 0, sizeof mat);
    for (int i = 0; i < V; i++)
      for (FlowEdge x : adj[i])
        mat[i][x.v] += x.c;

    vector<bool> vis(sz);
    queue<int> q;
    q.push(src);
    vis[src] = true;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int v = 0; v < sz; v++) {
        if (mat[u][v] > 0 && !vis[v]) {
          q.push(v);
          vis[v] = true;
        }
      }
    }

    vector<pair<int, int>> cut;
    for (int i = 0; i < sz; i++)
      for (int j = 0; j < sz; j++)
        if (vis[i] && !vis[j])
          // if there's an edge from i to j.
          if (mat_adj[i][j] > 0)
            cut.emplace_back(i, j);

    return cut;
  }

  vector<pair<int, int>> min_edge_cover() {
    bool covered[sz];
    for (int i = 0; i < sz; i++)
      covered[i] = false;
    vector<pair<int, int>> edge_cover;
    for (int i = 1; i < sz - 1; i++) {
      for (FlowEdge e : adj[i]) {
        if (e.cap == 0 || e.v > sz - 2)
          continue;
        if (e.c == 0) {
          edge_cover.emplace_back(pair<int, int>(i, e.v));
          covered[i] = true;
          covered[e.v] = true;
          break;
        }
      }
    }
    for (int i = 1; i < sz - 1; i++) {
      for (FlowEdge e : adj[i]) {
        if (e.cap == 0 || e.v > sz - 2)
          continue;
        if (e.c == 0)
          continue;
        if (!covered[i] || !covered[e.v]) {
          edge_cover.emplace_back(pair<int, int>(i, e.v));
          covered[i] = true;
          covered[e.v] = true;
        }
      }
    }
    return edge_cover;
  }

  vector<vector<int>> allFlow() {
    assert(calculated);
    vector<vector<int>> ret(V, vector<int>(V, 0));

    for (int i = 0; i < V; i++) {
      for (FlowEdge x : adj[i]) {
        if (x.is_rev)
          continue;
        // flow from vertex i to x.v
        ret[i][x.v] += x.cap - x.c;
      }
    }

    // for(int i = 0; i < V; i++) {
    //   for(int j  = 0; j < V; j++) {
    //     cout << ret[i][j] << ' ';
    //   }
    //   cout << endl;
    // }

    return ret;
  }

  void dfs_build_path(int u, vector<int> &path, vector<vector<int>> &mat_flow,
                      vector<vector<int>> &ans, vector<vector<int>> &adj) {
    path.emplace_back(u);

    if (u == this->snk) {
      ans.emplace_back(path);
      return;
    }

    for (int v : adj[u]) {
      if (mat_flow[u][v]) {
        mat_flow[u][v]--;
        dfs_build_path(v, path, mat_flow, ans, adj);
        return;
      }
    }
  }

  vector<vector<int>> get_all_paths(vector<vector<int>> &adj) {
    assert(calculated);

    vector<vector<int>> mat_flow = allFlow();
    vector<vector<int>> ans;
    ans.reserve(max_flow);

    for (int i = 0; i < max_flow; i++) {
      vector<int> path;
      path.reserve(V);
      dfs_build_path(this->src, path, mat_flow, ans, adj);
    }

    return ans;
  }

  void dfs_vc(int u, vector<bool> &vis, bool left, vector<vector<int>> &paths) {
    vis[u] = true;
    for (const FlowEdge &v : adj[u]) {
      if (vis[v.v])
        continue;
      // saturated edges goes from right to left
      if (left && paths[u][v.v] == 0)
        dfs_vc(v.v, vis, left ^ 1, paths);
      // non-saturated edges goes from left to right
      else if (!left && paths[v.v][u] == 1)
        dfs_vc(v.v, vis, left ^ 1, paths);
    }
  }

  vector<int> vertex_cover(const int max_left) {
    assert(calculated);
    vector<bool> vis(V);
    vector<bool> saturated(V, false);
    auto paths = this->allFlow();

    for (int i = 1; i <= max_left; ++i) {
      for (int j = max_left + 1; j < this->snk; ++j) {
        if (paths[i][j] > 0) {
          saturated[i] = true;
          saturated[j] = true;
          break;
        }
      }
      if (!saturated[i] && !vis[i])
        dfs_vc(i, vis, 1, paths);
    }

    vector<int> ans;
    for (int i = 1; i <= max_left; ++i)
      if (saturated[i] && !vis[i])
        ans.emplace_back(i);

    for (int i = max_left + 1; i < this->snk; ++i)
      if (saturated[i] && vis[i])
        ans.emplace_back(i);

    return ans;
  }
};