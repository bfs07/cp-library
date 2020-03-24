// REQUIRES bit.cpp!!
// REQUIRES point_compresion.cpp!!
int count_inversions(vector<int> &arr) {
  arr = compress(arr);
  int ans = 0;
  BIT bit(arr.size());
  for (int i = arr.size() - 1; i > 0; --i) {
    ans += bit.query(arr[i] - 1);
    bit.update(arr[i], 1);
  }
  return ans;
}