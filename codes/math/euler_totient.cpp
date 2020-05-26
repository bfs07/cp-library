/// Returns the amount of numbers less than or equal to n which are co-primes
/// to it.
int phi(int n) {
  int result = n;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      while (n % i == 0)
        n /= i;
      result -= result / i;
    }
  }

  if (n > 1)
    result -= result / n;
  return result;
}