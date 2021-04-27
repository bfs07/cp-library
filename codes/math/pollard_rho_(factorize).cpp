/// Copied from:
/// https://codeforces.com/contest/1305/submission/73826085
#include <bits/stdc++.h>
using namespace std;
#define rep(i, from, to) for (int i = from; i < (to); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

ull gcd(ull u, ull v) {
  if (u == 0 || v == 0)
    return v ^ u;
  int shift = __builtin_ctzll(u | v);
  u >>= __builtin_ctzll(u);
  do {
    v >>= __builtin_ctzll(v);
    if (u > v) {
      ull t = v;
      v = u;
      u = t;
    }
    v -= u;
  } while (v);
  return u << shift;
}

ull mod_mul(ull a, ull b, ull M) {
  ll ret = a * b - M * ull(1 / (double)M * a * b);
  return ret + M * (ret < 0) - M * (ret >= (ll)M);
}

ull mod_pow(ull b, ull e, ull mod) {
  ull ans = 1;
  for (; e; b = mod_mul(b, b, mod), e /= 2)
    if (e & 1)
      ans = mod_mul(ans, b, mod);
  return ans;
}

bool isPrime(ull n) {
  if (n < 2 || n % 6 % 4 != 1)
    return (n | 1) == 3;
  ull A[] = {2, 13, 23, 1662803}, s = __builtin_ctzll(n - 1), d = n >> s;
  for (auto a : A) { // ^ count trailing zeroes
    ull p = mod_pow(a % n, d, n), i = s;
    while (p != 1 && p != n - 1 && a % n && i--)
      p = mod_mul(p, p, n);
    if (p != n - 1 && i != s)
      return 0;
  }
  return 1;
}
typedef ull u64;
typedef unsigned int u32;

typedef __uint128_t u128;
// typedef __int128_t i128;
typedef long long i64;
typedef unsigned long long u64;

u64 hi(u128 x) { return (x >> 64); }
u64 lo(u128 x) { return (x << 64) >> 64; }
struct Mont {
  Mont(u64 n) : mod(n) {
    inv = n;
    rep(i, 0, 6) inv *= 2 - n * inv;
    r2 = -n % n;
    rep(i, 0, 4) if ((r2 <<= 1) >= mod) r2 -= mod;
    rep(i, 0, 5) r2 = mul(r2, r2);
  }
  u64 reduce(u128 x) const {
    u64 y = hi(x) - hi(u128(lo(x) * inv) * mod);
    return i64(y) < 0 ? y + mod : y;
  }
  u64 reduce(u64 x) const { return reduce(x); }
  u64 init(u64 n) const { return reduce(u128(n) * r2); }
  u64 mul(u64 a, u64 b) const { return reduce(u128(a) * b); }
  u64 mod, inv, r2;
};

ull pollard(ull n) {
  if (n == 9)
    return 3;
  if (n == 25)
    return 5;
  if (n == 49)
    return 7;
  if (n == 323)
    return 17;
  Mont mont(n);
  auto f = [n, &mont](ull x) { return mont.mul(x, x) + 1; };
  ull x = 0, y = 0, t = 0, prd = 2, i = 1, q;
  while (t++ % 32 || gcd(prd, n) == 1) {
    if (x == y)
      x = ++i, y = f(x);
    if ((q = mont.mul(prd, max(x, y) - min(x, y))))
      prd = q;
    x = f(x), y = f(f(y));
  }
  return gcd(prd, n);
}

unordered_set<ll> primes;
unordered_set<ll> seen;
set<ll> prm;
void factor(ull n) {
  if (n <= 1 || seen.count(n))
    return;
  seen.insert(n);
  if (isPrime(n)) {
    primes.insert(n);
    prm.insert(n);
  } else {
    ull x = pollard(n);
    factor(x), factor(n / x);
  }
}
signed main() {
  ull x;
  // Factorizes 3e4 numbers in less than 1 sec in my PC.
  for (int i = 0; i < 30000; i++) {
    prm.clear();
    seen.clear();
    cin >> x;
    factor(x);
    // for (ll y : prm) {
    //   cout << y << " ";
    //   while (x % y == 0)
    //     x /= y;
    // }
    // cout << endl;
    // assert(x == 1);
  }
  cout << endl;
}