struct Tree {
  int l, r, ind;
};
Tree query[311111];
int arr[311111];
int freq[1111111];
int ans[311111];
int block = sqrt(n), cont = 0;

bool cmp(Tree a, Tree b) {
  if (a.l / block == b.l / block)
    return a.r < b.r;
  return a.l / block < b.l / block;
}

void add(int pos) {
  freq[arr[pos]]++;
  if (freq[arr[pos]] == 1) {
    cont++;
  }
}
void del(int pos) {
  freq[arr[pos]]--;
  if (freq[arr[pos]] == 0)
    cont--;
}
int main() {
  int n;
  cin >> n;
  block = sqrt(n);

  for (int i = 0; i < n; i++) {
    cin >> arr[i];
    freq[arr[i]] = 0;
  }

  int m;
  cin >> m;

  for (int i = 0; i < m; i++) {
    cin >> query[i].l >> query[i].r;
    query[i].l--, query[i].r--;
    query[i].ind = i;
  }
  sort(query, query + m, cmp);

  int s, e;
  s = e = query[0].l;
  add(s);
  for (int i = 0; i < m; i++) {
    while (s > query[i].l)
      add(--s);
    while (s < query[i].l)
      del(s++);
    while (e < query[i].r)
      add(++e);
    while (e > query[i].r)
      del(e--);
    ans[query[i].ind] = cont;
  }
  for (int i = 0; i < m; i++)
    cout << ans[i] << endl;
}
