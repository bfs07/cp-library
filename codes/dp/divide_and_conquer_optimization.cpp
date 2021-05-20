/// Problem: Split the array into k buckets such that the cost of each bucket is
/// the square sum of each subarray.

// resize below
vector<int> last(MAXN, INF), dp(MAXN, INF);
// Cost for the subarray (l, r).
int C(int l, int r) {
  int val = 0;
  val += sq(sum(l, r));
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
  for (int i = optl; i <= min(mid, optr); ++i)
    best = min(best, {(i == 1 ? 0 : last[i - 1]) + C(i, mid), i});

  dp[mid] = best.first;
  const int opt = best.second;

  f(l, mid - 1, optl, opt);
  f(mid + 1, r, opt, optr);
}

// 1-indexed, change to 0-index if necessary.
int compute(const int k) {
  for (int i = 0; i < k; ++i) {
    f(1, n, 1, n);
    last.swap(dp);
  }

  return last[n];
}
