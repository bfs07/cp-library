struct Node {
  int pref, suf, tot, best;
  Node () {}
  Node(int pref, int suf, int tot, int best) : pref(pref), suf(suf), tot(tot), best(best) {}
};

const int MAXN = 2E5 + 10;
Node tree[5*MAXN];
int arr[MAXN];

Node query(const int l, const int r, const int i, const int j, const int pos) {
  
  if(l > r || l > j || r < i)
    return Node(-INF, -INF, -INF, -INF);

  if(i <= l && r <= j)
    return Node(tree[pos].pref, tree[pos].suf, tree[pos].tot, tree[pos].best);
  
  int mid = (l + r) / 2;
  Node left = query(l,mid,i,j,2*pos+1), right = query(mid+1,r,i,j,2*pos+2);
  Node x;
  x.pref = max({left.pref, left.tot, left.tot + right.pref});
  x.suf = max({right.suf, right.tot, right.tot + left.suf});
  x.tot = left.tot + right.tot;
  x.best = max({left.best,right.best, left.suf + right.pref});
  return x;
}

// Update arr[idx] to v
// ITS NOT DELTA!!!
void update(int l, int r, const int idx, const int v, const int pos) {
  if(l > r || l > idx || r < idx)
    return;

  if(l == idx && r == idx) {
    tree[pos] = Node(v, v, v, v);
    return;
  }

  int mid = (l + r)/2;
  update(l,mid,idx,v,2*pos+1); update(mid+1,r,idx,v,2*pos+2);
  l = 2*pos+1, r = 2*pos+2;
  tree[pos].pref = max({tree[l].pref, tree[l].tot, tree[l].tot + tree[r].pref});
  tree[pos].suf = max({tree[r].suf, tree[r].tot, tree[r].tot + tree[l].suf});
  tree[pos].tot = tree[l].tot + tree[r].tot;
  tree[pos].best = max({tree[l].best,tree[r].best, tree[l].suf + tree[r].pref});
}

void build(int l, int r, const int pos) {
  
  if(l == r) {
    tree[pos] = Node(arr[l], arr[l], arr[l], arr[l]);
    return;
  }
  
  int mid = (l + r)/2;
  build(l,mid,2*pos+1); build(mid+1,r,2*pos+2);
  l = 2*pos+1, r = 2*pos+2;
  tree[pos].pref = max({tree[l].pref, tree[l].tot, tree[l].tot + tree[r].pref});
  tree[pos].suf = max({tree[r].suf, tree[r].tot, tree[r].tot + tree[l].suf});
  tree[pos].tot = tree[l].tot + tree[r].tot;
  tree[pos].best = max({tree[l].best,tree[r].best, tree[l].suf + tree[r].pref});
}