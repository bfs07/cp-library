// Returns the amount of numbers greater than k from i to j
struct Tree {
  vector<int> vet;
};
Tree tree[4 * (int)3e4];
int arr[(int)5e4];

int query(int l, int r, int i, int j, int k, int pos) {
  if (l > j || r < i)
    return 0;

  if (i <= l && r <= j) {
    auto it = upper_bound(tree[pos].vet.begin(), tree[pos].vet.end(), k);
    return tree[pos].vet.end() - it;
  }

  int mid = (l + r) >> 1;
  return query(l, mid, i, j, k, 2 * pos + 1) +
         query(mid + 1, r, i, j, k, 2 * pos + 2);
}

void build(int l, int r, int pos) {
  if (l == r) {
    tree[pos].vet.pb(arr[l]);
    return;
  }

  int mid = (l + r) >> 1;
  build(l, mid, 2 * pos + 1);
  build(mid + 1, r, 2 * pos + 2);

  merge(tree[2 * pos + 1].vet.begin(), tree[2 * pos + 1].vet.end(),
        tree[2 * pos + 2].vet.begin(), tree[2 * pos + 2].vet.end(),
        back_inserter(tree[pos].vet));
}
