/// Copied from:
/// https://github.com/kth-competitive-programming/kactl/content/data-structures/LineContainer.h

// clang-format off
/// Uncomment the line below to get the minimum answer, otherwise it will try to
/// get the maximum answer.
// #define MINIMUM
struct Line {
  // f(x) = aX + b
  mutable int a, b, p;
  bool operator<(const Line &o) const { return a < o.a; }
  bool operator<(int x) const { return p < x; }
  // Use the methods below to get the real value of the attributes!!!
  int get_a() {
    #ifdef MINIMUM
    return -a;
    #else
    return a;
    #endif
  }
  int get_b() {
    #ifdef MINIMUM
    return -b;
    #else
    return b;
    #endif
  }
};

struct LineContainer : multiset<Line, less<>> {
  // (for doubles, use inf = 1/.0, div(a,b) = a/b)
  static const int inf = LLONG_MAX;
  int div(int a, int b) { // floored division
    return a / b - ((a ^ b) < 0 && a % b);
  }
  bool isect(iterator x, iterator y) {
    if (y == end())
      return x->p = inf, 0;
    if (x->a == y->a)
      x->p = x->b > y->b ? inf : -inf;
    else
      x->p = div(y->b - x->b, x->a - y->a);
    return x->p >= y->p;
  }
  /// Inserts the line a * x + b.
  ///
  /// Time Complexity: O(log n)
  void add(int a, int b) {
    #ifdef MINIMUM
    a = -a, b = -b;
    #endif
    auto z = insert({a, b, 0}), y = z++, x = y;
    while (isect(y, z))
      z = erase(z);
    if (x != begin() && isect(--x, y))
      isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p)
      isect(x, erase(y));
  }
  /// Query the best line such that a * x + b is maximum/minimum.
  ///
  /// Time Complexity: O(log n)
  int query(int x) {
    assert(!empty());
    auto l = *lower_bound(x);
    #ifdef MINIMUM
    return -(l.a * x + l.b);
    #else
    return l.a * x + l.b;
    #endif
  }
};
// clang-format on