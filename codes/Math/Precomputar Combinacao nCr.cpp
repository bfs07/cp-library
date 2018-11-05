int C[1123][1123];

int mod(int n) {return n%((int)1e9+7);}

int nCr(int n, int k) {
	for(int i = 0; i <= n; i++) {
		for(int j = 0; j <= min(i,k); j++) {
			if(j == 0 || j == i) {
				C[i][j] = 1;
			} else {
				C[i][j]=mod(C[i-1][j-1]+C[i-1][j]);
			}
		}
	}
}
