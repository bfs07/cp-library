class BIT2D
{
private:

  vector<vector<int>> bit1;
  vector<vector<int>> bit2;
  vector<vector<int>> bit3;
  vector<vector<int>> bit4;
  int n, m;

private:

  int low(int i)
  {
    return (i & (-i));
  }

  // update from (1, 1) to (x, y)
  void bit_update(const int x, const int y, const int delta)
  { 
    assert(x > 0 && y > 0 && x <= this->n && y <= this->m);

    for(int i = x, c = x - 1, d = y - 1; i <= this->n; i += this->low(i))
      for(int j = y; j <= this->m; j += this->low(j)) {
        this->bit1[i][j] += delta;
        this->bit2[i][j] += delta * d;
        this->bit3[i][j] += delta * c;
        this->bit4[i][j] += delta * c * d;
      }
  }

  // query from (1, 1) to (x, y)
  int bit_query(const int x, const int y)
  {
    assert(x > 0 && y > 0 && x <= this->n && y <= this->m);

    int a, b, c, d, e;
    a = b = c = 0;
    for(int i = x; i > 0; i -= low(i))
    {
      d = e = 0;
      for(int j = y; j > 0; j -= low(j))
      {
        d += bit1[i][j];
        e += bit2[i][j];
        b += bit3[i][j];
        c += bit4[i][j];
      }
      a += (d * y) - e;
    }

    return (a * x) - (b * y) + c;
  }

public:

  BIT2D(vector<vector<int>> &mat)
  {
    // OBS: BIT IS INDEXED FROM 1
    // THE USE OF 1-BASED MATRIX IS RECOMMENDED 

    this->build(mat);
  }

  BIT2D(int n, int m)
  {
    this->n = n;
    this->m = m;
    this->bit.resize(n + 2, vector<int>(m + 2, 0)); 
  }

  int build(vector<vector<int>> &mat)
  {
    // OBS: BIT IS INDEXED FROM 1
    // THE USE OF 1-BASED MATRIX IS RECOMMENDED
    assert(mat.front().front() == 0);
    this->n = (int)mat.size() - 1;
    this->m = (int)mat.front().size() - 1;

    this->bit1.resize(this->n + 2, vector<int>(this->m + 2, 0));
    this->bit2.resize(this->n + 2, vector<int>(this->m + 2, 0));
    this->bit3.resize(this->n + 2, vector<int>(this->m + 2, 0));
    this->bit4.resize(this->n + 2, vector<int>(this->m + 2, 0));

    for(int i = 1; i <= this->n; i++)
      for(int j = 1; j <= this->m; j++)
        this->update(i, j, mat[i][j]);
  }

  // point update
  void update(const int x, const int y, const int delta)
  {
    assert(x2 >= x1 && x1 > 0 && y2 >= y1 && y1 > 0);
    this->update(x, y, x, y, delta);
  }

  // range update
  void update(const int x1, const int y1, const int x2, const int y2, const int delta)
  {
    assert(x2 >= x1 && x1 > 0 && y2 >= y1 && y1 > 0);
    this->update(x1, y1, delta);
    this->update(x2 + 1, y1, -delta);
    this->update(x1, y2 + 1, -delta);
    this->update(x2 + 1, y2 + 1, delta);
  }

  // point query
  int query(const int x, const int y) 
  {
    return this->query(x, y, x, y);
  }

  // range query
  int query(const int x1, const int y1, const int x2, const int y2)
  {
    assert(x2 >= x1 && x1 > 0 && y2 >= y1 && y1 > 0);
    return this->bit_query(x2, y2) - this->bit_query(x1 - 1, y2) - this->bit_query(x2, y1 - 1) + this->bit_query(x1 - 1, y1 - 1);
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