/// Returns the index in the array which contains the minimum element. In case
/// of draw, it returns the first occurrence.
///
/// Time Complexity: O(log3(n))
int ternary_search(const vector<int> &arr) {
  int l = 0, r = (int)arr.size() - 1;
  while (r - l > 2) {
    int lc = l + (r - l) / 3;
    int rc = r - (r - l) / 3;
    // the function f(x) returns the element on the position x
    if (f(lc) > f(rc))
      // the function is going down, then the middle is on the right.
      l = lc;
    else
      r = rc;
  }
  // the range [l, r] contains the minimum element.

  int minn = INF, idx = -1;
  for (int i = l; i <= r; ++i)
    if (f(i) < minn) {
      idx = i;
      minn = f(i);
    }

  return idx;
}