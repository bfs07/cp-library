// RMQ min implementation
struct SPT {

  vector<vector<int> > table;
  vector<int> lg;

  SPT() {}

  int merge(const int &l, const int &r) {
    return min(l, r);
  }

  void build(const vector<int> &arr) {
    
    table.resize(log2(arr.size()) + 1, vector<int>(arr.size()));
    lg.resize((int)arr.size() + 1);
    for(int i = 2; i <= arr.size(); i++)
      lg[i] = lg[i/2] + 1;

    table[0] = arr;
    int pow2 = 1;

    for(int i = 1; i < table.size(); i++) {
      int lastsz = (int)(arr.size()) - pow2 + 1;
      for(int j = 0; j + pow2 < lastsz; j++) {
        table[i][j] = merge(table[i-1][j], table[i-1][j+pow2]);
      }
      pow2 <<= 1;
    }

  }

  void print() {
    int pow2 = 1;
    for(int i = 0; i < table.size(); i++) {
      int sz = (int)(table.front().size()) - pow2 + 1;
      for(int j = 0; j < sz; j++) {
        cout << table[i][j] << " \n"[(j+1) == sz];
      }
      pow2 <<= 1;
    }
  }

  int query(int l, int r) {
    assert(l <= r);
    int lgg = lg[(r - l + 1)];
    return merge(table[lgg][l], table[lgg][r - (1 << lgg) + 1]);
  }

};