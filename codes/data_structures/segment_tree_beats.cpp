#define MIN_UPDATE // supports for i in [l, r] do a[i] = min(a[i], x)
#define MAX_UPDATE // supports for i in [l, r] do a[i] = max(a[i], x)
#define ADD_UPDATE // supports for i in [l, r] a[i] += x

// clang-format off
class Seg_Tree_Beats {
  const static int INF = (sizeof(int) == 4 ? 1e9 : 2e18) + 1e5;

public:
  struct Node {
    int sum;
    #ifdef ADD_UPDATE
    int lazy = 0;
    #endif
    #ifdef MIN_UPDATE
    // Stores the maximum value, its frequency, and 2nd max value.
    int maxx, cnt_maxx, smaxx;
    #endif
    #ifdef MAX_UPDATE
    // Stores the minimum value, its frequency, and 2nd min value.
    int minn, cnt_minn, sminn;
    #endif
    Node() {}
    Node(const int val) : sum(val) {
      #ifdef MIN_UPDATE
      maxx = val, cnt_maxx = 1, smaxx = -INF;
      #endif
      #ifdef MAX_UPDATE
      minn = val, cnt_minn = 1, sminn = INF;
      #endif
    }
  };

private:
  // Range Sum
  Node merge_nodes(const Node &x, const Node &y) {
    Node node;
    node.sum = x.sum + y.sum;

    #ifdef MIN_UPDATE
    node.maxx = max(x.maxx, y.maxx);
    node.smaxx = max(x.smaxx, y.smaxx);
    node.cnt_maxx = 0;
    if (node.maxx == x.maxx)
      node.cnt_maxx += x.cnt_maxx;
    else
      node.smaxx = max(node.smaxx, x.maxx);
    if (node.maxx == y.maxx)
      node.cnt_maxx += y.cnt_maxx;
    else
      node.smaxx = max(node.smaxx, y.maxx);
    #endif

    #ifdef MAX_UPDATE
    node.minn = min(x.minn, y.minn);
    node.sminn = min(x.sminn, y.sminn);
    node.cnt_minn = 0;
    if (node.minn == x.minn)
      node.cnt_minn += x.cnt_minn;
    else
      node.sminn = min(node.sminn, x.minn);
    if (node.minn == y.minn)
      node.cnt_minn += y.cnt_minn;
    else
      node.sminn = min(node.sminn, y.minn);
    #endif
    return node;
  }

private:
  int n;

public:
  vector<Node> tree;

private:
  #ifdef MIN_UPDATE
  // in queries a[i] = min(a[i], x)
  void apply_update_min(const int pos, const int x) {
    Node &node = tree[pos];
    node.sum -= (node.maxx - x) * node.cnt_maxx;
    #ifdef MAX_UPDATE
    if (node.maxx == node.minn)
      node.minn = x;
    else if (node.maxx == node.sminn)
      node.sminn = x;
    #endif
    node.maxx = x;
  }
  #endif

  #ifdef MAX_UPDATE
  void apply_update_max(const int pos, const int x) {
    Node &node = tree[pos];
    node.sum += (x - node.minn) * node.cnt_minn;
    #ifdef MIN_UPDATE
    if (node.minn == node.maxx)
      node.maxx = x;
    else if (node.minn == node.smaxx)
      node.smaxx = x;
    #endif
    node.minn = x;
  }
  #endif

  #ifdef ADD_UPDATE
  void apply_update_sum(const int l, const int r, const int pos, const int v) {
    tree[pos].sum += (r - l + 1) * v;
    #ifdef ADD_UPDATE
    tree[pos].lazy += v;
    #endif
    #ifdef MIN_UPDATE
    tree[pos].maxx += v;
    tree[pos].smaxx += v;
    #endif
    #ifdef MAX_UPDATE
    tree[pos].minn += v;
    tree[pos].sminn += v;
    #endif
  }
  #endif

  void propagate(const int l, const int r, const int pos) {
    if (l == r)
      return;
    Node &node = tree[pos];
    const int c1 = 2 * pos + 1, c2 = 2 * pos + 2;

    #ifdef ADD_UPDATE
    if (node.lazy != 0) {
      const int mid = (l + r) / 2;
      apply_update_sum(l, mid, c1, node.lazy);
      apply_update_sum(mid + 1, r, c2, node.lazy);
      node.lazy = 0;
    }
    #endif

    #ifdef MIN_UPDATE
    // min update
    if (tree[c1].maxx > node.maxx)
      apply_update_min(c1, node.maxx);
    if (tree[c2].maxx > node.maxx)
      apply_update_min(c2, node.maxx);
    #endif

    #ifdef MAX_UPDATE
    // max_update
    if (tree[c1].minn < node.minn)
      apply_update_max(c1, node.minn);
    if (tree[c2].minn < node.minn)
      apply_update_max(c2, node.minn);
    #endif
  }

  Node _build(const int l, const int r, const vector<int> &arr, const int pos) {
    if (l == r)
      return tree[pos] = Node(arr[l]);

    const int mid = (l + r) / 2;
    return tree[pos] = merge_nodes(_build(l, mid, arr, 2 * pos + 1),
                                   _build(mid + 1, r, arr, 2 * pos + 2));
  }

  Node _query(const int l, const int r, const int i, const int j, const int pos,
              const Node &NEUTRAL_NODE) {
    propagate(l, r, pos);

    if (l > r || l > j || r < i)
      return NEUTRAL_NODE;

    if (i <= l && r <= j)
      return tree[pos];

    const int mid = (l + r) / 2;
    return merge_nodes(_query(l, mid, i, j, 2 * pos + 1, NEUTRAL_NODE),
                       _query(mid + 1, r, i, j, 2 * pos + 2, NEUTRAL_NODE));
  }

  #ifdef ADD_UPDATE
  Node _update_sum(const int l, const int r, const int i, const int j,
                   const int v, const int pos) {
    propagate(l, r, pos);

    if (l > r || l > j || r < i)
      return tree[pos];

    if (i <= l && r <= j) {
      apply_update_sum(l, r, pos, v);
      return tree[pos];
    }

    int mid = (l + r) / 2;
    return tree[pos] =
               merge_nodes(_update_sum(l, mid, i, j, v, 2 * pos + 1),
                           _update_sum(mid + 1, r, i, j, v, 2 * pos + 2));
  }
  #endif

  #ifdef MIN_UPDATE
  Node _update_min(const int l, const int r, const int i, const int j,
                   const int x, const int pos) {
    propagate(l, r, pos);

    if (l > r || l > j || r < i || tree[pos].maxx <= x)
      return tree[pos];

    if (i <= l && r <= j && tree[pos].smaxx < x) {
      apply_update_min(pos, x);
      return tree[pos];
    }

    const int mid = (l + r) / 2;
    return tree[pos] =
               merge_nodes(_update_min(l, mid, i, j, x, 2 * pos + 1),
                           _update_min(mid + 1, r, i, j, x, 2 * pos + 2));
  }
  #endif

  #ifdef MAX_UPDATE
  Node _update_max(const int l, const int r, const int i, const int j,
                   const int x, const int pos) {
    propagate(l, r, pos);

    if (l > r || l > j || r < i || tree[pos].minn >= x)
      return tree[pos];

    if (i <= l && r <= j && tree[pos].sminn > x) {
      apply_update_max(pos, x);
      return tree[pos];
    }

    const int mid = (l + r) / 2;
    return tree[pos] =
               merge_nodes(_update_max(l, mid, i, j, x, 2 * pos + 1),
                           _update_max(mid + 1, r, i, j, x, 2 * pos + 2));
  }
  #endif

  void build(const vector<int> &arr) {
    this->tree.resize(4 * this->n);
    this->_build(0, this->n - 1, arr, 0);
  }

public:
  /// N equals to -1 means the Segment Tree hasn't been created yet.
  Seg_Tree_Beats() : n(-1) {}

  /// Constructor responsible for initializing the tree with 0's.
  ///
  /// Time Complexity O(n)
  Seg_Tree_Beats(const int n) : n(n) {
    this->tree.resize(4 * this->n, Node(0));
  }

  /// Constructor responsible for building the tree based on a vector.
  ///
  /// Time Complexity O(n)
  Seg_Tree_Beats(const vector<int> &arr) : n(arr.size()) { this->build(arr); }

  #ifdef ADD_UPDATE
  /// Range update from l to r.
  /// Type: for i in range [l, r] do a[i] += x
  void update_sum(const int l, const int r, const int x) {
    assert(this->n >= 0);
    assert(0 <= l), assert(l <= r), assert(r < this->n);
    this->_update_sum(0, this->n - 1, l, r, x, 0);
  }
  #endif

  #ifdef MIN_UPDATE
  /// Range update from l to r.
  /// Type: for i in range [l, r] do a[i] = min(a[i], x)
  void update_min(const int l, const int r, const int x) {
    assert(this->n >= 0);
    assert(0 <= l), assert(l <= r), assert(r < this->n);
    this->_update_min(0, this->n - 1, l, r, x, 0);
  }
  #endif

  #ifdef MAX_UPDATE
  /// Range update from l to r.
  /// Type: for i in range [l, r] do a[i] = max(a[i], x)
  void update_max(const int l, const int r, const int x) {
    assert(this->n >= 0);
    assert(0 <= l), assert(l <= r), assert(r < this->n);
    this->_update_max(0, this->n - 1, l, r, x, 0);
  }
  #endif

  /// Range Sum query from l to r.
  ///
  /// Time Complexity O(log n)
  int query_sum(const int l, const int r) {
    assert(this->n >= 0);
    assert(0 <= l), assert(l <= r), assert(r < this->n);
    return this->_query(0, this->n - 1, l, r, 0, Node(0)).sum;
  }

  #ifdef MAX_UPDATE
  /// Range Min query from l to r.
  ///
  /// Time Complexity O(log n)
  int query_min(const int l, const int r) {
    assert(this->n >= 0);
    assert(0 <= l), assert(l <= r), assert(r < this->n);
    return this->_query(0, this->n - 1, l, r, 0, Node(INF)).minn;
  }
  #endif

  #ifdef MIN_UPDATE
  /// Range Max query from l to r.
  ///
  /// Time Complexity O(log n)
  int query_max(const int l, const int r) {
    assert(this->n >= 0);
    assert(0 <= l), assert(l <= r), assert(r < this->n);
    return this->_query(0, this->n - 1, l, r, 0, Node(-INF)).maxx;
  }
  #endif
};
// clang-format on
// OBS: Q updates of the type a[i] = (min/max)(a[i], x) have the amortized
// complexity of O(q * (log(n) ^ 2)).