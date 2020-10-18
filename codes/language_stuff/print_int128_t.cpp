void print(__int128_t x) {
  if (x == 0)
    return void(cout << 0 << endl);
  bool neg = false;
  if (x < 0) {
    neg = true;
    x *= -1;
  }
  string ans;
  while (x) {
    ans += char(x % 10 + '0');
    x /= 10;
  }

  if (neg)
    ans += "-";
  reverse(all(ans));
  cout << ans << endl;
}