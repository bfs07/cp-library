// NOT TESTED YET
vector<vector<int>> bit;
void init() {
  bit.resize(n);
  for(vector<int> &x: bit)
    x.resize(m, 0);
}

int query(int x, int y) {
  int ret = 0;
  for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
    for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
      ret += bit[i][j];
  return ret;
}

void update(int x, int y, int delta) {
  for (int i = x; i < n; i = i | (i + 1))
    for (int j = y; j < m; j = j | (j + 1))
      bit[i][j] += delta;
  }