map<int, int> primeFactors(int n) {
	set<int> ret;
  while (n%2 == 0) {
  	m[2]++;
    n = n/2;
  }
 
 	int sq = sqrt(n);
  for (int i = 3; i <= sq+2; i = i+2) {
    while (n%i == 0) {
    	m[i]++;;
      n = n/i;
    }
    /* OBS1
	IF(N < 1E7)
		FATORE COM SPF
    */
  }

  if (n > 2) 
  	m[n]++;

  return ret;
}
