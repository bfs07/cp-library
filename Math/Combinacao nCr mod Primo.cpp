inv[1] = 1;
for(int i = 2; i < m; ++i)
  inv[i] = (m - (m/i) * inv[m%i] % m) % m;

factorial[0] = 1;
for (int i = 1; i <= MAXN; i++) {
  factorial[i] = factorial[i - 1] * i % m;
}

int binomial_coefficient(int n, int k) {
  return factorial[n] * inverse(factorial[k]) % m * inverse(factorial[n - k]) % m;
}