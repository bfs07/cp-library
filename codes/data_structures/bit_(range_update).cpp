/// INDEX THE ARRAY BY 1!!!
class BIT {
private:
  vector<int> bit1, bit2;
  int n;

private:
  int low(int i) { return i & (-i); }

  // Point update
  void update(int i, const int delta, vector<int> &bit) {
    while (i <= n) {
      bit[i] += delta;
      i += low(i);
    }
  }

  // Prefix query
  int query(int i, const vector<int> &bit) {
    int sum = 0;
    while (i > 0) {
      sum += bit[i];
      i -= low(i);
    }
    return sum;
  }

  // Builds the bit
  void build(const vector<int> &arr) {
    // OBS: BIT IS INDEXED FROM 1
    // THE USAGE OF 1-BASED ARRAY IS MANDATORY
    assert(arr.front() == 0);
    this->n = (int)arr.size() - 1;
    bit1.resize(arr.size(), 0);
    bit2.resize(arr.size(), 0);

    for (int i = 1; i <= n; i++)
      update(i, arr[i]);
  }

public:
  /// Constructor responsible for initializing the tree with 0's.
  ///
  /// Time Complexity: O(n log n)
  BIT(const vector<int> &arr) { build(arr); }

  /// Constructor responsible for building the tree based on a vector.
  ///
  /// Time Complexity O(n)
  BIT(const int n) {
    // OBS: BIT IS INDEXED FROM 1
    // THE USAGE OF 1-INDEXED ARRAY IS MANDATORY
    this->n = n;
    bit1.resize(n + 1, 0);
    bit2.resize(n + 1, 0);
  }

  /// Range update from l to r.
  ///
  /// Time Complexity O(log n)
  void update(const int l, const int r, const int delta) {
    assert(1 <= l), assert(l <= r), assert(r <= n);
    update(l, delta, bit1);
    update(r + 1, -delta, bit1);
    update(l, delta * (l - 1), bit2);
    update(r + 1, -delta * r, bit2);
  }

  /// Update at a single index.
  ///
  /// Time Complexity O(log n)
  void update(const int i, const int delta) {
    assert(1 <= i), assert(i <= n);
    update(i, i, delta);
  }

  /// Range query from l to r.
  ///
  /// Time Complexity O(log n)
  int query(const int l, const int r) {
    assert(1 <= l), assert(l <= r), assert(r <= n);
    return query(r) - query(l - 1);
  }

  /// Prefix query from 1 to i.
  ///
  /// Time Complexity O(log n)
  int query(const int i) {
    assert(i <= n);
    return (query(i, bit1) * i) - query(i, bit2);
  }
};