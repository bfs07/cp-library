/// Problem: Split the array into k buckets such that the cost of each bucket is
/// the square sum of each subarray.

// Cost for splitting the subarray (l, n - 1) into (l, r - 1), (r, n - 1).
int C(int l, int r) {
  int val = 0;
  // remove the cost for the range(l, n - 1)
  val -= sq(sum(l, n));
  // adding the cost for the range(l, r - 1)
  val += sq(sum(l, r - 1));
  // adding the cost for the range(r, n - 1)
  val += sq(sum(r, n));
  return val;
}

/// dp[i] represents the cost of spliting the array into k buckets (after k
/// iterations), with the index i as the last index.
///
/// Time Complexity: O(n*k*(log n))
void f(int l, int r, int optl, int optr) {
  if (l > r)
    return;

  int mid = (l + r) / 2;
  auto best = make_pair(INF, INF); // change to (-INF, -INF) to maximize
  // change mid - 1 to mid if buckets can intercept.
  for (int i = optl; i <= min(mid - 1, optr); ++i)
    best = min(best, {last[i] + C(i, mid), i});

  dp[mid] = best.first;
  int opt = best.second;

  f(l, mid - 1, optl, opt);
  f(mid + 1, r, opt, optr);
}
