int kadane(int arr[], int l) {
	
	int soma, total;	
	soma = total = arr[0];
	
	for(int i = 1; i < l; i++) {
		soma = max(arr[i], arr[i] +soma);
		if(soma > total)
			total = soma;
	}
	return total;
	
}
