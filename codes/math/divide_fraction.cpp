/// Prints precision floating point places of a / b.
string divide(int a, int b, const int precision) {
  assert(a < b);
  string ans;
  for (int i = 0; i < precision; ++i) {
    a *= 10;
    ans += a / b + '0';
    a %= b;
  }
  return ans;
}