/// INDEX THE ARRAY BY 1!!!
class BIT {
private:
  vector<int> bit;
  int n;

private:
  int low(const int i) { return (i & (-i)); }

  // point update
  void bit_update(int i, const int delta) {
    while (i <= this->n) {
      this->bit[i] += delta;
      i += this->low(i);
    }
  }

  // point query
  int bit_query(int i) {
    int sum = 0;
    while (i > 0) {
      sum += bit[i];
      i -= this->low(i);
    }
    return sum;
  }

public:
  BIT(const vector<int> &arr) { this->build(arr); }

  BIT(const int n) {
    // OBS: BIT IS INDEXED FROM 1
    // THE USE OF 1-BASED ARRAY IS RECOMMENDED
    this->n = n;
    this->bit.resize(n + 1, 0);
  }

  // build the bit
  void build(const vector<int> &arr) {
    // OBS: BIT IS INDEXED FROM 1
    // THE USE OF 1-BASED ARRAY IS RECOMMENDED
    assert(arr.front() == 0);
    this->n = (int)arr.size() - 1;
    this->bit.resize(arr.size(), 0);

    for (int i = 1; i <= this->n; i++)
      this->bit_update(i, arr[i]);
  }

  // point update
  void update(const int i, const int delta) {
    assert(1 <= i), assert(i <= this->n);
    this->bit_update(i, delta);
  }

  // point query
  int query(const int i) {
    assert(1 <= i), assert(i <= this->n);
    return this->bit_query(i);
  }

  // range query
  int query(const int l, const int r) {
    assert(1 <= l), assert(l <= r), assert(r <= this->n);
    return this->bit_query(r) - this->bit_query(l - 1);
  }
};