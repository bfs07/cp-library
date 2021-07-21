// INDEX BY ONE ALWAYS!!!
class BIT_2D {
private:
  // row, column
  const int n, m;
  vector<vector<int>> tree;

private:
  // Returns an integer which constains only the least significant bit.
  int low(const int i) { return i & (-i); }

  void _update(const int x, const int y, const int delta) {
    for (int i = x; i < n; i += low(i))
      for (int j = y; j < m; j += low(j))
        tree[i][j] += delta;
  }

  int _query(const int x, const int y) {
    int ans = 0;
    for (int i = x; i > 0; i -= low(i))
      for (int j = y; j > 0; j -= low(j))
        ans += tree[i][j];
    return ans;
  }

public:
  // put the size of the array without 1 indexing.
  /// Time Complexity: O(n * m)
  BIT_2D(const int n, const int m) : n(n + 1), m(m + 1) {
    tree.resize(this->n, vector<int>(this->m, 0));
  }

  /// Time Complexity: O(n * m * (log(n) + log(m)))
  BIT_2D(const vector<vector<int>> &mat)
      : n(mat.size()), m(mat.front().size()) {
    // Check if it is 1 indexed.
    assert(mat[0][0] == 0);
    tree.resize(n, vector<int>(m, 0));
    for (int i = 1; i < n; i++)
      for (int j = 1; j < m; j++)
        _update(i, j, mat[i][j]);
  }

  /// Query from (1, 1) to (x, y).
  ///
  /// Time Complexity: O(log(n) + log(m))
  int prefix_query(const int x, const int y) {
    assert(0 < x), assert(x < n);
    assert(0 < y), assert(y < m);
    return _query(x, y);
  }

  /// Query from (x1, y1) to (x2, y2).
  ///
  /// Time Complexity: O(log(n) + log(m))
  int query(const int x1, const int y1, const int x2, const int y2) {
    assert(0 < x1), assert(x1 <= x2), assert(x2 < n);
    assert(0 < y1), assert(y1 <= y2), assert(y2 < m);
    return _query(x2, y2) - _query(x1 - 1, y2) - _query(x2, y1 - 1) +
           _query(x1 - 1, y1 - 1);
  }

  /// Updates point (x, y).
  ///
  /// Time Complexity: O(log(n) + log(m))
  void update(const int x, const int y, const int delta) {
    assert(0 < x), assert(x < n);
    assert(0 < y), assert(y < m);
    _update(x, y, delta);
  }
};