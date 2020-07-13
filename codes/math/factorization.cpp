/// Factorizes a number.
///
/// Time Complexity: O(sqrt(n))
map<int, int> factorize(int n) {
  map<int, int> fat;
  while (n % 2 == 0) {
    ++fat[2];
    n /= 2;
  }

  for (int i = 3; i * i <= n; i += 2) {
    while (n % i == 0) {
      ++fat[i];
      n /= i;
    }
    /* OBS1
        IF(N < 1E7)
          you can optimize by factoring with SPF
    */
  }
  if (n > 2)
    ++fat[n];
  return fat;
}
