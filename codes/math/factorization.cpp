map<int, int> primeFactors(int n) {
  set<int> ret;
  while (n % 2 == 0) {
    ++m[2];
    n /= 2;
  }

  for (int i = 3; i * i <= n; i += 2) {
    while (n % i == 0) {
      m[i]++;
      n = n / i;
    }
    /* OBS1
        IF(N < 1E7)
          you can optimize by factoring with SPF
    */
  }

  if (n > 2)
    ++m[n];

  return ret;
}
