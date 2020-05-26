const int MAXN = 1e6;

/// Contains all the primes in the segments
vector<int> segPrimes;
bitset<MAXN + 5> primesInSeg;

/// smallest prime factor
int spf[MAXN + 5];

vector<int> primes;
bitset<MAXN + 5> isPrime;

void sieve(int n = MAXN + 2) {

  for (int i = 0; i <= n; i++)
    spf[i] = i;

  isPrime.set();
  for (int i = 2; i <= n; i++) {
    if (!isPrime[i])
      continue;

    for (int j = i * i; j <= n; j += i) {
      isPrime[j] = false;
      spf[j] = min(i, spf[j]);
    }
    primes.emplace_back(i);
  }
}

vector<int> getFactorization(int x) {
  vector<int> ret;
  while (x != 1) {
    ret.emplace_back(spf[x]);
    x = x / spf[x];
  }
  return ret;
}

/// Gets all primes from l to r
void segSieve(int l, int r) {
  // primes from l to r
  // transferred to 0..(l-r)
  segPrimes.clear();
  primesInSeg.set();
  int sq = sqrt(r) + 5;

  for (int p : primes) {
    if (p > sq)
      break;

    for (int i = l - l % p; i <= r; i += p) {
      if (i - l < 0)
        continue;

      // if i is less than 1e6, it could be checked in the
      // array of the sieve
      if (i >= (int)1e6 || !isPrime[i])
        primesInSeg[i - l] = false;
    }
  }

  for (int i = 0; i < r - l + 1; i++) {
    if (primesInSeg[i])
      segPrimes.emplace_back(i + l);
  }
}
