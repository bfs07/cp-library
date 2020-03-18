/// Works for the polynomial f(x) = z1*x + z0
class Seg_Tree {
public:
  struct Node {
    int val, z1, z0;

    Node() {}
    Node(const int val, const int z1, const int z0)
        : val(val), z1(z1), z0(z0) {}
  };

private:
  // range sum
  Node NEUTRAL_NODE = Node(0, 0, 0);
  Node merge_nodes(const Node &x, const Node &y) {
    return Node(x.val + y.val, 0, 0);
  }
  void apply_lazy(const int l, const int r, const int pos) {
    tree[pos].val += (r - l + 1) * tree[pos].z0;
    tree[pos].val += (r - l) * (r - l + 1) / 2 * tree[pos].z1;
  }

private:
  int n;

public:
  vector<Node> tree;

private:
  void st_propagate(const int l, const int r, const int pos) {
    if (tree[pos].z0 != 0 || tree[pos].z1 != 0) {
      apply_lazy(l, r, pos);
      int mid = (l + r) / 2;
      int sz_left = mid - l + 1;
      if (l != r) {
        tree[2 * pos + 1].z0 += tree[pos].z0;
        tree[2 * pos + 1].z1 += tree[pos].z1;

        tree[2 * pos + 2].z0 += tree[pos].z0 + sz_left * tree[pos].z1;
        tree[2 * pos + 2].z1 += tree[pos].z1;
      }
      tree[pos].z0 = 0;
      tree[pos].z1 = 0;
    }
  }

  Node st_build(const int l, const int r, const vector<int> &arr,
                const int pos) {
    if (l == r)
      return tree[pos] = Node(arr[l], 0, 0);

    int mid = (l + r) / 2;
    return tree[pos] = merge_nodes(st_build(l, mid, arr, 2 * pos + 1),
                                   st_build(mid + 1, r, arr, 2 * pos + 2));
  }

  Node st_query(const int l, const int r, const int i, const int j,
                const int pos) {
    st_propagate(l, r, pos);

    if (l > r || l > j || r < i)
      return NEUTRAL_NODE;

    if (i <= l && r <= j)
      return tree[pos];

    int mid = (l + r) / 2;
    return merge_nodes(st_query(l, mid, i, j, 2 * pos + 1),
                       st_query(mid + 1, r, i, j, 2 * pos + 2));
  }

  // it adds a number delta to the range from i to j
  Node st_update(const int l, const int r, const int i, const int j,
                 const int z1, const int z0, const int pos) {
    st_propagate(l, r, pos);

    if (l > r || l > j || r < i)
      return tree[pos];

    if (i <= l && r <= j) {
      tree[pos].z0 = (l - i + 1) * z0;
      tree[pos].z1 = z1;
      st_propagate(l, r, pos);
      return tree[pos];
    }

    int mid = (l + r) / 2;
    return tree[pos] =
               merge_nodes(st_update(l, mid, i, j, z1, z0, 2 * pos + 1),
                           st_update(mid + 1, r, i, j, z1, z0, 2 * pos + 2));
  }

public:
  Seg_Tree() : n(-1) {}

  Seg_Tree(const int n) : n(n) { this->tree.resize(4 * this->n, Node(0, 0)); }

  Seg_Tree(const vector<int> &arr) { this->build(arr); }

  void build(const vector<int> &arr) {
    this->n = arr.size();
    this->tree.resize(4 * this->n);
    this->st_build(0, this->n - 1, arr, 0);
  }

  /// Index update of a polynomial f(x) = z1*x + z0
  ///
  /// Time Complexity O(log n)
  void update(const int i, const int z1, const int z0) {
    assert(this->n >= 0);
    assert(0 <= i), assert(i < this->n);
    this->st_update(0, this->n - 1, i, i, z1, z0, 0);
  }

  /// Range update of a polynomial f(x) = z1*x + z0 from l to r
  ///
  /// Time Complexity O(log n)
  void update(const int l, const int r, const int z1, const int z0) {
    assert(this->n >= 0);
    assert(0 <= l), assert(l <= r), assert(r < this->n);
    this->st_update(0, this->n - 1, l, r, z1, z0, 0);
  }

  /// Range sum query from l to r
  ///
  /// Time Complexity O(log n)
  int query(const int l, const int r) {
    assert(this->n >= 0);
    assert(0 <= l), assert(l <= r), assert(r < this->n);
    return this->st_query(0, this->n - 1, l, r, 0).val;
  }
};