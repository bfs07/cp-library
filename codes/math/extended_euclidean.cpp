/// Returns a tuple containing the gcd(a, b) and the roots for
/// a*x + b*y = gcd(a, b).
///
/// Time Complexity: O(log(min(a, b))).
tuple<uint, int, int> extended_gcd(uint a, uint b) {
  int x = 0, y = 1, x1 = 1, y1 = 0;
  while (a != 0) {
    uint q = b / a;
    tie(x, x1) = make_pair(x1, x - q * x1);
    tie(y, y1) = make_pair(y1, y - q * y1);
    tie(a, b) = make_pair(b % a, a);
  }
  return make_tuple(b, x, y);
}