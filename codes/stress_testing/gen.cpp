#include <bits/stdc++.h>

using namespace std;

#define eb emplace_back
#define ii pair<int, int>
#define OK (cerr << "OK" << endl)
#define debug(x) cerr << #x " = " << (x) << endl
#define ff first
#define ss second
#define int long long
#define tt tuple<int, int, int>
#define all(x) x.begin(), x.end()
#define vi vector<int>
#define vii vector<pair<int, int>>
#define vvi vector<vector<int>>
#define vvii vector<vector<pair<int, int>>>
#define Matrix(n, m, v) vector<vector<int>>(n, vector<int>(m, v))
#define endl '\n'

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// Generates a string of (n) characters from 'a' to 'a' + (c)
string str(const int n, const int c);
// Generates (size) strings of (n) characters from 'a' to 'a' + (c)
string spaced_str(const int n, const int size, const int c);
// Generates a string of (n) 01 characters.
string str01(const int n);
// Generates a number in the range [l, r].
int num(const int l, const int r);
// Generates a vector of (n) numbers in the range [l, r].
vector<int> vec(const int n, const int l, const int r);
// Generates a matrix of (n x m) numbers in the range [l, r].
vector<vector<int>> matrix(const int n, const int m, const int l, const int r);
// Generates a tree with n vertices
vector<pair<int, int>> tree(const int n);
// Generates a forest with n vertices.
vector<pair<int, int>> forest(const int n);
// Generates a connected graph with n vertices.
vector<pair<int, int>> connected_graph(const int n);
// Generates a graph with n vertices.
vector<pair<int, int>> graph(const int n);

signed main() {
  int t = num(1, 1);
  // cout << t << endl;
  while (t--) {
    int n = num(1, 2e5);
    int m = num(1, 2e5);
    cout << n << endl;
  }
}

vector<pair<int, int>> tree(const int n) {
  const int root = num(1, n);
  vector<int> v1, v2;
  v1.emplace_back(root);
  for (int i = 1; i <= n; ++i)
    if (i != root)
      v2.emplace_back(i);
  random_shuffle(all(v2));
  vector<pair<int, int>> edges;
  while (!v2.empty()) {
    const int idx = num(0, (int)v1.size() - 1);
    edges.emplace_back(v1[idx], v2.back());
    v1.emplace_back(v2.back());
    v2.pop_back();
  }
  return edges;
}

vector<pair<int, int>> forest(const int n) {
  int val = n;
  vector<pair<int, int>> edges;
  int oft = 0;
  while (val > 0) {
    const int cur = num(1, val);
    auto e = tree(cur);
    for (auto [u, v] : e)
      edges.emplace_back(u + oft, v + oft);
    val -= cur;
    oft += cur;
  }
  return edges;
}

vector<pair<int, int>> connected_graph(const int n) {
  auto e = tree(n);
  set<pair<int, int>> s(e.begin(), e.end());
  const int ERROR = n;
  int q = num(0, max(0ll, (n - 1) * (n - 2)) / 2 + ERROR);
  while (q--) {
    int u = num(1, n), v = num(1, n);
    if (u == v || s.count(make_pair(u, v)) || s.count(make_pair(v, u)))
      continue;
    e.emplace_back(u, v);
    s.emplace(u, v);
  }
  return e;
}

vector<pair<int, int>> graph(const int n) {
  int q = num(0, n * (n - 1) / 2);
  set<pair<int, int>> s;
  while (q--) {
    int u = num(1, n), v = num(1, n);
    if (u == v)
      continue;
    if (u > v)
      swap(u, v);
    s.emplace(u, v);
  }
  vector<pair<int, int>> edges;
  for (auto [u, v] : s) {
    if (rng() % 2)
      swap(u, v);
    edges.eb(u, v);
  }
  return edges;
}

int num(const int l, const int r) {
  int sz = r - l + 1;
  int n = rng() % sz;
  return n + l;
}

vector<int> vec(const int n, const int l, const int r) {
  vector<int> arr(n);
  for (int &x : arr)
    x = num(l, r);
  return arr;
}

vector<vector<int>> matrix(const int n, const int m, const int l, const int r) {
  vector<vector<int>> mt;
  for (int i = 0; i < n; ++i)
    mt.emplace_back(vec(m, l, r));
  return mt;
}

string str(const int n, const int c = 26) {
  string ans;
  for (int i = 0; i < n; ++i)
    ans += char(rng() % c + 'a');
  return ans;
}

string str01(const int n) {
  string ans;
  for (int i = 0; i < n; ++i) {
    ans += char(rng() % 2 + '0');
  }
  return ans;
}

string spaced_str(const int n, const int size, const int c = 26) {
  string ans;
  for (int i = 0; i < size; ++i) {
    if (i)
      ans += ' ';
    ans += str(n, c);
  }
  return ans;
}