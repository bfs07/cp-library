/// INDEX THE ARRAY BY 1!!!
class BIT {
private:
  vector<int> bit;
  int n;

private:
  int low(const int i) { return i & (-i); }

  // Point update
  void bit_update(int i, const int delta) {
    while (i <= n) {
      bit[i] += delta;
      i += low(i);
    }
  }

  // Prefix query
  int bit_query(int i) {
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
    bit.resize(arr.size(), 0);

    for (int i = 1; i <= n; i++)
      bit_update(i, arr[i]);
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
    // THE USAGE OF 1-BASED ARRAY IS MANDATORY
    this->n = n;
    bit.resize(n + 1, 0);
  }

  /// Update at a single index.
  ///
  /// Time Complexity O(log n)
  void update(const int i, const int delta) {
    assert(1 <= i), assert(i <= n);
    bit_update(i, delta);
  }

  /// Prefix query from 1 to i.
  ///
  /// Time Complexity O(log n)
  int query(const int i) {
    assert(1 <= i), assert(i <= n);
    return bit_query(i);
  }

  /// Range query from l to r.
  ///
  /// Time Complexity O(log n)
  int query(const int l, const int r) {
    assert(1 <= l), assert(l <= r), assert(r <= n);
    return bit_query(r) - bit_query(l - 1);
  }
};