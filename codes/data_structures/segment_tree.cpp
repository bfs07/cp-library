class Seg_Tree {
public:
  struct Node {
    int val, lazy;

    Node() {}
    Node(const int val) : val(val), lazy(0) {}
  };

private:
  // // Range Sum
  // Node NEUTRAL_NODE = Node(0);
  // Node merge_nodes(const Node &x, const Node &y) {
  //   return Node(x.val + y.val);
  //   ;
  // }
  // void apply_lazy(const int l, const int r, const int pos) {
  //   // for set change this to =
  //   tree[pos].val += (r - l + 1) * tree[pos].lazy;
  // }

  // // RMQ Max
  // Node NEUTRAL_NODE = Node(-INF);
  // Node merge_nodes(const Node &x, const Node &y) {
  //   return Node(max(x.val, y.val));
  // }
  // void apply_lazy(const int l, const int r, const int pos) {
  //   tree[pos].val += tree[pos].lazy;
  // }

  // // RMQ Min
  // Node NEUTRAL_NODE = Node(INF);
  // Node merge_nodes(const Node &x, const Node &y) {
  //   return Node(min(x.val, y.val));
  // }
  // void apply_lazy(const int l, const int r, const int pos) {
  //   tree[pos].val += tree[pos].lazy;
  // }

  // // XOR
  // // Only works with point updates
  // Node NEUTRAL_NODE = Node(0);
  // Node merge_nodes(const Node &x, const Node &y) {
  //   return Node(x.val ^ y.val);
  //   ;
  // }
  // void apply_lazy(const int l, const int r, const int pos) {}

private:
  int n;

public:
  vector<Node> tree;

private:
  void propagate(const int l, const int r, const int pos) {
    if (tree[pos].lazy != 0) {
      apply_lazy(l, r, pos);
      if (l != r) {
        // for set change this to =
        tree[2 * pos + 1].lazy += tree[pos].lazy;
        tree[2 * pos + 2].lazy += tree[pos].lazy;
      }
      tree[pos].lazy = 0;
    }
  }

  Node _build(const int l, const int r, const vector<int> &arr, const int pos) {
    if (l == r)
      return tree[pos] = Node(arr[l]);

    int mid = (l + r) / 2;
    return tree[pos] = merge_nodes(_build(l, mid, arr, 2 * pos + 1),
                                   _build(mid + 1, r, arr, 2 * pos + 2));
  }

  int _get_first(const int l, const int r, const int i, const int j,
                 const int v, const int pos) {
    propagate(l, r, pos);

    if (l > r || l > j || r < i)
      return -1;
    // Needs RMQ MAX
    // Replace to <= for greater or (with RMQ MIN) > for smaller or
    // equal or >= for smaller
    if (tree[pos].val < v)
      return -1;

    if (l == r)
      return l;

    int mid = (l + r) / 2;
    int aux = _get_first(l, mid, i, j, v, 2 * pos + 1);
    if (aux != -1)
      return aux;
    return _get_first(mid + 1, r, i, j, v, 2 * pos + 2);
  }

  Node _query(const int l, const int r, const int i, const int j,
              const int pos) {
    propagate(l, r, pos);

    if (l > r || l > j || r < i)
      return NEUTRAL_NODE;

    if (i <= l && r <= j)
      return tree[pos];

    int mid = (l + r) / 2;
    return merge_nodes(_query(l, mid, i, j, 2 * pos + 1),
                       _query(mid + 1, r, i, j, 2 * pos + 2));
  }

  // It adds a number delta to the range from i to j
  Node _update(const int l, const int r, const int i, const int j,
               const int delta, const int pos) {
    propagate(l, r, pos);

    if (l > r || l > j || r < i)
      return tree[pos];

    if (i <= l && r <= j) {
      tree[pos].lazy = delta;
      propagate(l, r, pos);
      return tree[pos];
    }

    int mid = (l + r) / 2;
    return tree[pos] =
               merge_nodes(_update(l, mid, i, j, delta, 2 * pos + 1),
                           _update(mid + 1, r, i, j, delta, 2 * pos + 2));
  }

  void build(const vector<int> &arr) {
    this->tree.resize(4 * this->n);
    this->_build(0, this->n - 1, arr, 0);
  }

public:
  /// N equals to -1 means the Segment Tree hasn't been created yet.
  Seg_Tree() : n(-1) {}

  /// Constructor responsible for initializing a tree with 0.
  ///
  /// Time Complexity O(n)
  Seg_Tree(const int n) : n(n) { this->tree.resize(4 * this->n, Node(0)); }

  /// Constructor responsible for building the initial tree based on a vector.
  ///
  /// Time Complexity O(n)
  Seg_Tree(const vector<int> &arr) : n(arr.size()) { this->build(arr); }

  /// Returns the first index from i to j compared to v.
  /// Uncomment the line in the original function to get the proper element that
  /// may be: GREATER OR EQUAL, GREATER, SMALLER OR EQUAL, SMALLER.
  ///
  /// Time Complexity O(log n)
  int get_first(const int i, const int j, const int v) {
    assert(this->n >= 0);
    return this->_get_first(0, this->n - 1, i, j, v, 0);
  }

  /// Update at a single index.
  ///
  /// Time Complexity O(log n)
  void update(const int idx, const int delta) {
    assert(this->n >= 0);
    assert(0 <= idx), assert(idx < this->n);
    this->_update(0, this->n - 1, idx, idx, delta, 0);
  }

  /// Range update from l to r.
  ///
  /// Time Complexity O(log n)
  void update(const int l, const int r, const int delta) {
    assert(this->n >= 0);
    assert(0 <= l), assert(l <= r), assert(r < this->n);
    this->_update(0, this->n - 1, l, r, delta, 0);
  }

  /// Query at a single index.
  ///
  /// Time Complexity O(log n)
  int query(const int idx) {
    assert(this->n >= 0);
    assert(0 <= idx), assert(idx < this->n);
    return this->_query(0, this->n - 1, idx, idx, 0).val;
  }

  /// Range query from l to r.
  ///
  /// Time Complexity O(log n)
  int query(const int l, const int r) {
    assert(this->n >= 0);
    assert(0 <= l), assert(l <= r), assert(r < this->n);
    return this->_query(0, this->n - 1, l, r, 0).val;
  }
};