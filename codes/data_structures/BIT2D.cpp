// INDEX BY ONE ALWAYS!!!
class BIT_2D {
 private:
  // row, column
  int n, m;
  vector<vector<int>> tree;

 private:
  // Returns an integer which constains only the least significant bit.
  int low(int i) {
    return i & (-i);
  }

  void bit_update(const int x, const int y, const int delta) {
    for(int i = x; i < n; i += low(i))
      for(int j = y; j < m; j += low(j))
        this->tree[i][j] += delta;
  }

  int bit_query(const int x, const int y) {
    int ans = 0;
    for(int i = x; i > 0; i -= low(i))
      for(int j = y; j > 0; j -= low(j))
        ans += this->tree[i][j];

    return ans;
  }

 public:
  // put the size of the array without 1 indexing.
  /// Time Complexity: O(n * m)
  BIT_2D(int n, int m) {
    this->n = n + 1;
    this->m = m + 1;

    this->tree.resize(n, vector<int>(m, 0));
  }

  /// Time Complexity: O(n * m * (log(n) + log(m)))
  BIT_2D(const vector<vector<int>> &mat) {
    // Check if it is 1 index.
    assert(mat[0][0] == 0);
    this->n = mat.size();
    this->m = mat.front().size();
    
    this->tree.resize(n, vector<int>(m, 0));
    for(int i = 1; i < n; i++)
      for(int j = 1; j < m; j++)
        update(i, j, mat[i][j]);
  }

  /// Query from (1, 1) to (x, y).
  ///
  /// Time Complexity: O(log(n) + log(m))
  int prefix_query(const int x, const int y) {
    assert(0 < x); assert(x < this->n);
    assert(0 < y); assert(y < this->m);

    return bit_query(x, y);
  }

  /// Query from (x1, y1) to (x2, y2).
  ///
  /// Time Complexity: O(log(n) + log(m))
  int query(const int x1, const int y1, const int x2, const int y2) {
    assert(0 < x1); assert(x1 <= x2); assert(x2 < this->n);
    assert(0 < y1); assert(y1 <= y2); assert(y2 < this->m);

    return bit_query(x2, y2) - bit_query(x1 - 1, y2) - bit_query(x2, y1 - 1) + bit_query(x1 - 1, y1 - 1);
  }

  /// Updates point (x, y).
  ///
  /// Time Complexity: O(log(n) + log(m))
  void update(const int x, const int y, const int delta) {
    assert(0 < x); assert(x < this->n);
    assert(0 < y); assert(y < this->m);

    bit_update(x, y, delta);  
  }
};