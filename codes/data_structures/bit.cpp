// #define RANGE_SUM
// #define RANGE_UPDATE
// Uncomment ONLY ONE above!
// clang-format off
class BIT {
private:
  vector<int> bit;
  const int n, offset;

private:
  int low(const int i) { return i & (-i); }

  // Point update
  void _update(int i, const int delta) {
    while (i <= n) {
      bit[i] += delta;
      i += low(i);
    }
  }

  // Prefix query
  int _query(int i) {
    int sum = 0;
    while (i > 0) {
      sum += bit[i];
      i -= low(i);
    }
    return sum;
  }

  void build(const vector<int> &arr) {
    bit.resize(arr.size() + offset, 0);
    for (int i = 1; i <= n; i++)
      #ifdef RANGE_UPDATE
      update(i - offset, i - offset, arr[i - offset]);
      #endif
      #ifdef RANGE_SUM
      update(i - offset, arr[i - offset]);
      #endif
  }

public:
  /// Constructor responsible for initializing the tree with 0's.
  ///
  /// Time Complexity: O(n log n)
  BIT(const vector<int> &arr, const int indexed_from)
      : n(arr.size() - indexed_from), offset(indexed_from ^ 1) {
    assert(indexed_from == 0 || indexed_from == 1);
    build(arr);
  }

  /// Constructor responsible for building the tree based on a vector.
  ///
  /// Time Complexity O(n)
  BIT(const int n, const int indexed_from) : n(n), offset(indexed_from ^ 1) {
    bit.resize(n + 1, 0);
  }

  #ifdef RANGE_UPDATE
  void update(int l, int r, const int val) {
    l += offset, r += offset;
    assert(1 <= l), assert(l <= r), assert(r <= n);
    _update(l, val);
    _update(r + 1, -val);
  }
  #endif

  #ifdef RANGE_SUM
  /// Update at a single index.
  ///
  /// Time Complexity O(log n)
  void update(int idx, const int delta) {
    idx += offset;
    assert(1 <= idx), assert(idx <= n);
    _update(idx, delta);
  }
  #endif

  #ifdef RANGE_UPDATE
  /// Query at a single index.
  ///
  /// Time Complexity O(log n)
  int query(int idx) {
    idx += offset;
    assert(1 <= idx), assert(idx <= n);
    return _query(idx);
  }
  #endif

  #ifdef RANGE_SUM
  /// Range query from l to r.
  ///
  /// Time Complexity O(log n)
  int query(int l, int r) {
    l += offset, r += offset;
    assert(1 <= l), assert(l <= r), assert(r <= n);
    return _query(r) - _query(l - 1);
  }
  #endif
};
// clang-format on