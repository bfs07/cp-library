class BIT2D
{
private:

  vector<vector<int>> bit;
  int n, m;

private:

  int low(int i)
  {
    return (i & (-i));
  }

public:

  BIT2D(vector<vector<int>> &mat)
  {
    // OBS: BIT IS INDEXED FROM 1
    // THE USE OF 1-BASED MATRIX IS RECOMMENDED 

    assert(mat.front().front() == 0);
    this->n = (int)mat.size() - 1;
    this->m = (int)mat.front().size() - 1;
    this->bit.resize(this->n + 1, vector<int>(this->m + 1, 0));

    this->build(mat);
  }

  BIT2D(int n, int m)
  {
    this->n = n;
    this->m = m;
    this->bit.resize(n + 1, vector<int>(m, 0)); 
  }

  int build(vector<vector<int>> &mat)
  {
    // OBS: BIT IS INDEXED FROM 1
    // THE USE OF 1-BASED MATRIX IS RECOMMENDED

    for(int i = 1; i <= this->n; i++)
      for(int j = 1; j <= this->m; j++)
        this->update(i, j, mat[i][j]);
  }

  void update(const int x, const int y, const int delta)
  { 
    for(int i = x; i <= this->n; i += this->low(i))
      for(int j = y; j <= this->m; j += this->low(j)) 
        this->bit[i][j] += delta;
  }

  int query(const int x, const int y)
  {
    int sum = 0;
    for(int i = x; i > 0; i -= this->low(i))
      for(int j = y; j > 0; j -= this->low(j))
        sum += this->bit[i][j];

    return sum;
  }

  int query(const int x1, const int y1, const int x2, const int y2) {
    assert(x2 >= x1 && x1 > 0 && y2 >= y1 && y1 > 0);
    return this->query(x2, y2) - this->query(x1 - 1, y2) - this->query(x2, y1 - 1) + this->query(x1 - 1, y1 - 1);
  }

};

// TESTS
// signed main() {

//   vector<vector<int>> mat = {
//                               {0,0,0,0},
//                               {0,1,2,3},
//                               {0,4,5,6},
//                               {0,7,8,9},
//                               {0,10,11,12}
//                             };

//   BIT2D b2d(mat);

//   assert(b2d.query(1,1,1,2) == 3);
//   assert(b2d.query(1,1,1,1) == 1);
//   assert(b2d.query(1,1,4,3) == 78);
//   assert(b2d.query(1,1,2,2) == 12);
//   assert(b2d.query(2,2,4,3) == 51);
//   assert(b2d.query(2,2,3,3) == 28);
// }