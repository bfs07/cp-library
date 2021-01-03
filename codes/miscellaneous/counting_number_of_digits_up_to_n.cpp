int solve(int n) {
  int maxx = 9, minn = 1, dig = 1, ret = 0;
  for (int i = 1; i <= 17; i++) {
    int q = min(maxx, n);
    ret += max(0ll, (q - minn + 1) * dig);
    maxx = (maxx * 10 + 9), minn *= 10, dig++;
  }
  return ret;
}