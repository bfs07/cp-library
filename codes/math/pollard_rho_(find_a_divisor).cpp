// Requires binary_exponentiation.cpp

/// Returns a prime divisor for n.
///
/// Expected Time Complexity: O(n1/4)
int pollard_rho(const int n) {
  srand(time(NULL));

  /* no prime divisor for 1 */
  if (n == 1)
    return n;

  if (n % 2 == 0)
    return 2;

  /* we will pick from the range [2, N) */
  int x = (rand() % (n - 2)) + 2;
  int y = x;

  /* the constant in f(x).
   * Algorithm can be re-run with a different c
   * if it throws failure for a composite. */
  int c = (rand() % (n - 1)) + 1;

  /* Initialize candidate divisor (or result) */
  int d = 1;

  /* until the prime factor isn't obtained.
  If n is prime, return n */
  while (d == 1) {
    /* Tortoise Move: x(i+1) = f(x(i)) */
    x = (modular_pow(x, 2, n) + c + n) % n;

    /* Hare Move: y(i+1) = f(f(y(i))) */
    y = (modular_pow(y, 2, n) + c + n) % n;
    y = (modular_pow(y, 2, n) + c + n) % n;

    d = __gcd(abs(x - y), n);

    /* retry if the algorithm fails to find prime factor
     * with chosen x and c */
    if (d == n)
      return pollard_rho(n);
  }

  return d;
}
