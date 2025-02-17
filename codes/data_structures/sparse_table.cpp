class Sparse_Table {
private:
  /// Sparse table min
  // int merge(const int l, const int r) { return min(l, r); }
  /// Sparse table max
  // int merge(const int l, const int r) { return max(l, r); }

private:
  int n;
  vector<vector<int>> table;
  vector<int> lg;

private:
  /// lg[i] represents the log2(i)
  void build_log_array() {
    lg.resize(this->n + 1);
    for (int i = 2; i <= this->n; i++)
      lg[i] = lg[i / 2] + 1;
  }

  /// Time Complexity: O(n*log(n))
  void build_sparse_table(const vector<int> &arr) {
    table.resize(lg[this->n] + 1, vector<int>(this->n));

    table[0] = arr;
    int pow2 = 1;
    for (int i = 1; i < table.size(); i++) {
      const int lastsz = this->n - pow2 + 1;
      for (int j = 0; j + pow2 < lastsz; j++)
        table[i][j] = merge(table[i - 1][j], table[i - 1][j + pow2]);
      pow2 <<= 1;
    }
  }

public:
  /// Constructor that builds the log array and the sparse table.
  ///
  /// Time Complexity: O(n*log(n))
  Sparse_Table(const vector<int> &arr) : n(arr.size()) {
    this->build_log_array();
    this->build_sparse_table(arr);
  }

  void print() {
    int pow2 = 1;
    for (int i = 0; i < table.size(); i++) {
      const int sz = (int)(table.front().size()) - pow2 + 1;
      for (int j = 0; j < sz; j++)
        cout << table[i][j] << " \n"[(j + 1) == sz];
      pow2 <<= 1;
    }
  }

  /// Range query from l to r.
  ///
  /// Time Complexity: O(1)
  int query(const int l, const int r) {
    assert(0 <= l), assert(l <= r), assert(r < this->n);
    int lgg = lg[r - l + 1];
    return merge(table[lgg][l], table[lgg][r - (1 << lgg) + 1]);
  }
};