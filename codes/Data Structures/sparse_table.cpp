// RMQ min implementation
class Sparse_Table {

 private:
  int n;
  vector<vector<int> > table;
  vector<int> lg;

  Sparse_Table() {}

  int merge(const int &l, const int &r) {
    return min(l, r);
  }

  void build_log_array()

  void build_sparse_table(const vector<int> &arr) {
    
    table.resize(log2(this->n) + 1, vector<int>(this->n));
    lg.resize((int)this->n + 1);
    for(int i = 2; i <= this->n; i++)
      lg[i] = lg[i/2] + 1;

    table[0] = arr;
    int pow2 = 1;

    for(int i = 1; i < table.size(); i++) {
      int lastsz = (int)(this->n) - pow2 + 1;
      for(int j = 0; j + pow2 < lastsz; j++) {
        table[i][j] = merge(table[i-1][j], table[i-1][j+pow2]);
      }
      pow2 <<= 1;
    }

  }

 public:
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