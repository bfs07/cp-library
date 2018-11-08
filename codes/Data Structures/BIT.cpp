// SIZE = N
int bit[(int)2e5+3];
int arr[(int)2e5+3];

int low(int i) {
	return (i & (-i));
}

void update(int i, int v, int n) {
	
	while(i <= n) {
		bit[i] += v;
		i += low(i);
	}

}

int query(int i) {

	int sum = 0;
	while(i > 0) {
		sum += bit[i];
		i -= low(i);
	}

	return sum;

}

int build(int n) {

	// OBS: BIT IS INDEXED FROM 1
	// RECOMMENDED USE 1-BASED ARRAY

	memset(bit, 0, (n+3)*sizeof(int));

	for(int i = 1; i <= n; i++) {
		update(i, arr[i], n);
	}
}
