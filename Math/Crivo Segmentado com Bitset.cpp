bitset<(int)1e5+3> primesInSeg;
bitset<(int)1e6+3> isPrime;
vector<int> primes;
vector<int> segPrimes;

void sieve(int n = (int)1e6) {

	isPrime.set();
	for(int i = 2; i*i <= n; i++) {
		if(!isPrime[i])
			continue;

		for(int j = i*i; j <= n; j+=i) {
			isPrime[j] = false;
		}
		primes.pb(i);
	}
}

void segSieve(int l, int r) {
	// primos de l..r
	// transladados de 0..(l-r)
	segPrimes.clear();
	primesInSeg.set();
	int sq = sqrt(r);

	for(int p: primes) {
		if(p > sq)
			break;

		for(int i = l - l%p; i <= r; i += p) {
			if(i - l < 0)
				continue;

			// se i for menor q 1e6 checa na array do crivo
			if(i >= (int)1e6 || !isPrime[i])
				primesInSeg[i-l] = false;
		}
	}

	for(int i = 0; i < r-l+1; i++) {
		if(primesInSeg[i])
			segPrimes.pb(i+l);
	}
}
