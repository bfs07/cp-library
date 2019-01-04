int bit[(int)3e5];

int lowbit(int x) {
  return (x & (-x));
}

void update(int i, int v, int n) {

  while(i <= n) {
    
    bit[i] += v;

    i += lowbit(i);
  }
}

int query(int i, int n) {

    int sum = 0;

    while(i > 0) {
      sum += bit[i];

      i -= lowbit(i);
    } 

    return sum;
}
