class Seg_Tree {
 public:
  struct Node {    
    int val, lazy;

    Node() {}
    Node(const int val, const int lazy) : val(val), lazy(lazy) {}
  };
 private:
  // // range sum
  // Node NEUTRAL_NODE = Node(0, 0);
  // Node merge_nodes(const Node &x, const Node &y) {
  //   return Node(x.val + y.val, 0);
  // }
  // void apply_lazy(const int l, const int r, const int pos) {
  //   tree[pos].val += (r - l + 1) * tree[pos].lazy;
  // }

  // RMQ max
  Node NEUTRAL_NODE = Node(-INF, 0);
  Node merge_nodes(const Node &x, const Node &y) {
    return Node(max(x.val, y.val), 0);
  }
  void apply_lazy(const int l, const int r, const int pos) {
    tree[pos].val += tree[pos].lazy; 
  }

  // // RMQ min
  // Node NEUTRAL_NODE = Node(INF, 0);
  // Node merge_nodes(const Node &x, const Node &y) {
  //   return Node(min(x.val, y.val), 0);
  // }
  // void apply_lazy(const int l, const int r, const int pos) {
  //   tree[pos].val += tree[pos].lazy; 
  // }

 private:
  int n;
  vector<Node> tree;

 private:
  void st_propagate(const int l, const int r, const int pos) {
    if(tree[pos].lazy != 0) {
      apply_lazy(l, r, pos);
      if(l != r) {
        tree[2*pos+1].lazy += tree[pos].lazy;
        tree[2*pos+2].lazy += tree[pos].lazy;
      }
      tree[pos].lazy = 0;
    }
  }

  Node st_build(const int l, const int r, const vector<int> &arr, const int pos) {
    if(l == r)
      return tree[pos] = Node(arr[l], 0);

    int mid = (l + r) / 2;
    return tree[pos] = merge_nodes(st_build(l, mid, arr, 2*pos+1), st_build(mid + 1, r, arr, 2*pos+2));
  }

  Node st_query(const int l, const int r, const int i, const int j, const int pos) { 
    st_propagate(l, r, pos);

    if(l > r || l > j || r < i)
      return NEUTRAL_NODE;

    if(i <= l && r <= j)
      return tree[pos];

    int mid = (l + r) / 2;
    return merge_nodes(st_query(l, mid, i, j, 2*pos+1), st_query(mid+1, r, i, j, 2*pos+2));
  }

  // it adds a number delta to the range from i to j
  Node st_update(const int l, const int r, const int i, const int j, const int delta, const int pos) {
    st_propagate(l, r, pos);

    if(l > r || l > j || r < i)
      return tree[pos];

    if(i <= l && r <= j) {
      tree[pos].lazy += delta;
      st_propagate(l, r, pos);
      return tree[pos];
    }

    int mid = (l + r) / 2;
    return tree[pos] = merge_nodes(st_update(l, mid, i, j, delta, 2*pos+1), st_update(mid+1, r, i, j, delta, 2*pos+2));
  }
  
 public:
  Seg_Tree() {
    this->n = -1;
  }

  Seg_Tree(const int n) {
    this->n = n + 1;
    this->tree.resize(4*this->n, Node(0, 0));
  }

  Seg_Tree(const vector<int> &arr) {
    this->build(arr);
  }

  void build(const vector<int> &arr) {
    this->n = arr.size() + 1;
    this->tree.resize(4*this->n);
    this->st_build(0, this->n - 1, arr, 0);
  }

  // update at a single index
  void update(const int i, const int delta) {
    assert(this->n >= 0);
    assert(0 <= i); assert(i < this->n);
    this->st_update(0, this->n - 1, i, i, delta, 0);
  }

  // range update
  void update(const int l, const int r, const int delta) {
    assert(this->n >= 0);
    assert(0 <= l); assert(l <= r); assert(r < this->n);
    this->st_update(0, this->n - 1, l, r, delta, 0);
  }

  int query(const int l, const int r) {
    assert(this->n >= 0);
    assert(0 <= l); assert(l <= r); assert(r < this->n);
    return this->st_query(0, this->n - 1, l, r, 0).val;
  }
};