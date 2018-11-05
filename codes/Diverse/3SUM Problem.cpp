// vetor arr e valor x, a soma de três valores desse vetor deve ser igual a x

bool sum3(int arr[], int x, int n) {
	sort(arr,arr + n); 
	for(int i = 0; i < n-2; i++) {
		int l = i+1, r = n-1; 
	/* 2SUM problem -> ponteiro que aponta para o primeiro e ultimo da sequencia e caso a soma for menor do que x adianta em uma casa o ponteiro da esquerda caso seja maior diminui em uma casa o ponteiro da direita */
		while(l < r) {
			if(arr[i] + arr[l] + arr[r] == x) {
				return true;
			} else if(arr[i] + arr[l] + arr[r] < x) 
				l++;
			else 
				r--;
		}
	}
	return false;
}
