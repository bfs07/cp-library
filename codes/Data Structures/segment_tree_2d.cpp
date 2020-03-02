// REQUIRES segment_tree.cpp!!
class Seg_Tree_2d {
 private:
  // // range sum
  // int NEUTRAL_VALUE = 0;
  // int merge_nodes(const int &x, const int &y) {
  //   return x + y;
  // }

  // // RMQ max
  // int NEUTRAL_VALUE = -INF;
  // int merge_nodes(const int &x, const int &y) {
  //   return max(x, y);
  // }

  // // RMQ min
  // int NEUTRAL_VALUE = INF;
  // int merge_nodes(const int &x, const int &y) {
  //   return min(x, y);
  // }
 
 private:
  int n, m;

 public:
  vector<Seg_Tree> tree;

 private:
  void st_build(const int l, const int r, const int pos, const vector<vector<int>> &mat) {
    if(l == r)
      tree[pos] = Seg_Tree(mat[l]);
    else {
      int mid = (l + r) / 2;
      st_build(l, mid, 2*pos + 1, mat);
      st_build(mid + 1, r, 2*pos + 2, mat);
      for(int i = 0; i < tree[2*pos + 1].tree.size(); i++)
        tree[pos].tree[i].val = merge_nodes(tree[2*pos + 1].tree[i].val, 
                                            tree[2*pos + 2].tree[i].val);
    }
  }

  int st_query(const int l, const int r, const int x1, const int y1, const int x2, const int y2, const int pos) {
    if(l > x2 || r < x1) 
      return NEUTRAL_VALUE;

    if(x1 <= l && r <= x2) 
      return tree[pos].query(y1, y2);

    int mid = (l + r) / 2;
    return merge_nodes(st_query(l, mid, x1, y1, x2, y2, 2*pos + 1), 
                       st_query(mid + 1, r, x1, y1, x2, y2, 2*pos + 2));
  }

  void st_update(const int l, const int r, const int x, const int y, const int delta, const int pos) {
    if(l > x || r < x) 
      return;

    // Only supports point updates.
    if(l == r) {
      tree[pos].update(y, delta);
      return;
    }

    int mid = (l + r) / 2;
    st_update(l, mid, x, y, delta, 2*pos + 1);
    st_update(mid + 1, r, x, y, delta, 2*pos + 2);
    tree[pos].update(y, delta);
  }   

 public:
  Seg_Tree_2d() {
    this->n = -1;
    this->m = -1;
  }

  Seg_Tree_2d(const int n, const int m) {
    this->n = n;
    this->m = m;
    // MAY TLE IN BUILD, TEST IT OR UPDATE EACH NODE MANUALLY!
    assert(m < 10000);
    tree.resize(4 * n, Seg_Tree(m));
  }

  Seg_Tree_2d(const int n, const int m, const vector<vector<int>> &mat) {
    this->n = n;
    this->m = m;
    // MAY TLE IN BUILD, TEST IT OR UPDATE EACH NODE MANUALLY!
    assert(m < 10000);
    tree.resize(4 * n, Seg_Tree(m));
    st_build(0, n - 1, 0, mat);
  }

  // Query from (x1, y1) to (x2, y2).
  //
  // Time complexity: O((log n) * (log m)) 
  int query(const int x1, const int y1, const int x2, const int y2) {
    assert(this->n > -1);
    assert(0 <= x1); assert(x1 <= x2); assert(x2 < this->n);
    assert(0 <= y1); assert(y1 <= y2); assert(y2 < this->n);
    return st_query(0, this->n - 1, x1, y1, x2, y2, 0);
  }

  // Point updates on position (x, y).
  //
  // Time complexity: O((log n) * (log m)) 
  void update(const int x, const int y, const int delta) {
    assert(0 <= x); assert(x < this->n);
    assert(0 <= y); assert(y < this->n);
    st_update(0, this->n - 1, x, y, delta, 0);
  }
};