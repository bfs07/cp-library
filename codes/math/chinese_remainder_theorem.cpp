int inv(int a, int m) {
  int m0 = m, t, q;
  int x0 = 0, x1 = 1;

  if (m == 1)
    return 0;

  // Apply extended Euclid Algorithm
  while (a > 1) {
    // q is quotient
    if (m == 0)
      return INF;
    q = a / m;
    t = m;
    // m is remainder now, process same as euclid's algo
    m = a % m, a = t;
    t = x0;
    x0 = x1 - q * x0;
    x1 = t;
  }

  // Make x1 positive
  if (x1 < 0)
    x1 += m0;

  return x1;
}
// k is size of num[] and rem[].  Returns the smallest
// number x such that:
//  x % num[0] = rem[0],
//  x % num[1] = rem[1],
//  ..................
//  x % num[k-2] = rem[k-1]
// Assumption: Numbers in num[] are pairwise coprimes
// (gcd for every pair is 1)
int findMinX(const vector<int> &num, const vector<int> &rem, const int k) {
  // Compute product of all numbers
  int prod = 1;
  for (int i = 0; i < k; i++)
    prod *= num[i];

  int result = 0;

  // Apply above formula
  for (int i = 0; i < k; i++) {
    int pp = prod / num[i];
    int iv = inv(pp, num[i]);
    if (iv == INF)
      return INF;
    result += rem[i] * inv(pp, num[i]) * pp;
  }

  // IF IS NOT VALID RETURN INF
  return (result % prod == 0 ? INF : result % prod);
}