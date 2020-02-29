class Persistent_Seg_Tree {
  struct Node {
    int val;
    Node *left, *right;
    Node() {}
    Node(int v, Node *l, Node *r) : val(v), left(l), right(r) {}
  };
  #define NEUTRAL_NODE Node(0, nullptr, nullptr);
  Node _NEUTRAL_NODE = Node(0, nullptr, nullptr);

 public:
  int merge_nodes(const int x, const int y) {
    return x + y;
  }

 private:
  int n;
  vector<Node*> version;

 public:
  /// Builds version[0] with the values in the array.
  ///
  /// Time complexity: O(n)
  Node* pst_build(Node *node, const int l, const int r, const vector<int> &arr) {
    node = new NEUTRAL_NODE;
    if(l == r) {
      node->val = arr[l];
      return node;
    }

    int mid = (l + r) / 2;
    node->left = pst_build(node->left, l, mid, arr);
    node->right = pst_build(node->right, mid + 1, r, arr);
    node->val = merge_nodes(node->left->val, node->right->val);
    return node;
  }

  /// Builds version[0] with 0.
  ///
  /// Time complexity: O(n)
  Node* pst_build_empty(Node *node, const int l, const int r) {
    node = new NEUTRAL_NODE;
    if(l == r)
      return node;

    int mid = (l + r) / 2;
    node->left = pst_build_empty(node->left, l, mid);
    node->right = pst_build_empty(node->right, mid + 1, r);
    node->val = merge_nodes(node->left->val, node->right->val);
    return node;
  }

  Node* pst_update(Node *cur_tree, Node *prev_tree, const int l, const int r, const int idx, const int v) {
    if(l > idx || r < idx) {
      if(cur_tree != nullptr)
        return cur_tree;
      return prev_tree;
    }

    if(cur_tree == nullptr)
      cur_tree = new Node(prev_tree->val, nullptr, nullptr);

    if(l == r) {
      cur_tree->val += v;
      return cur_tree;
    }

    int mid = (l + r) / 2;
    cur_tree->left = pst_update(cur_tree->left, prev_tree->left, l, mid, idx, v);
    cur_tree->right = pst_update(cur_tree->right, prev_tree->right, mid + 1, r, idx, v);
    cur_tree->val = merge_nodes(cur_tree->left->val, cur_tree->right->val);
    return cur_tree;
  }

  int pst_query(Node *node, const int l, const int r, const int i, const int j) {
    if(l > j || r < i)
      return _NEUTRAL_NODE.val;

    if(i <= l && r <= j) 
      return node->val;

    int mid = (l + r) / 2;
    return merge_nodes(pst_query(node->left, l, mid, i, j), pst_query(node->right, mid + 1, r, i, j));
  }

 public: 
  Persistent_Seg_Tree(const int n, const int number_of_versions) {
    this->n = n;
    version.resize(number_of_versions);
    this->version[0] = this->pst_build_empty(this->version[0], 0, this->n - 1);
  }

  /// Constructor that allows to pass initial values to the leafs.
  Persistent_Seg_Tree(const int n, const int number_of_versions, vector<int> &arr) {
    this->n = n;
    version.resize(number_of_versions);
    this->version[0] = this->pst_build(this->version[0], 0, this->n - 1, arr);
  }

  /// Updates an index in cur_tree based on prev_tree.
  ///
  /// Time complexity: O(log(n))
  void update(const int cur_version, const int prev_version, const int idx, const int v) {
    this->version[cur_version] = this->pst_update(this->version[cur_version], this->version[prev_version], 0, this->n - 1, idx, v);
  }

  /// Query from l to r.
  ///
  /// Time complexity: O(log(n))
  int query(const int version, const int l, const int r) {
    assert(0 <= l); assert(l <= r); assert(r < this->n);
    return this->pst_query(this->version[version], 0, this->n - 1, l, r);
  }
};