// |A ∪ B ∪ C|=|A|+|B|+|C|-|A ∩ B|-|A ∩ C|-|B ∩ C|+|A ∩ B ∩ C|

// EXEMPLO: Quantos números de 1 a 10^9 são múltiplos de 42, 54, 137 ou 201?

int f(vector<int> arr, int LIMIT) {

	int n = arr.size();
	int c = 0;

	for(int mask = 1; mask < (1<<n); mask++) {
		int lcm = 1;
		for(int i = 0; i < n; i++) 
			if(mask&(1<<i))
				lcm=lcm*arr[i]/__gcd(lcm,arr[i]);
		// se o numero de conjutos a unir for impar entao soma  
		if(__builtin_popcount(mask) %2 == 1)
			c += LIMIT/lcm;
		else // se nao subtrai
			c -= LIMIT/lcm; 		
	}

	return LIMIT-c;

}	
