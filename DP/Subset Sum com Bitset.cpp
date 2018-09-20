bitset<312345> bit;
int arr[112345];
void subsetSum(int n) {
	bit.reset();
	bit.set(0);
	for(int i = 0; i < n; i++) {
		bit |= (bit << arr[i]);
	}
}