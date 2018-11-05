int power(int x, int p, int MOD) {
	if(p == 0)
		return 1%MOD;
	if(p == 1) 
		return x%MOD;
	int res = power(x, p/2, MOD);
	res = (long long)res*res%MOD;
	if(p&1) 
		res = (long long)res*x%MOD;
	return res;
}
