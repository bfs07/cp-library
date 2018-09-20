int lis(vector<int> t){
	vector<int> lis;
	for(int i = 0 ; i < t.size() ; i ++){
		int l = 0 , r = lis.size();
		r--;
		int ansj = - 1;
		while(l<=r){
			int mid = (l+r)/2;
			// OBS: PARA >= TROCAR AQUI EMBAIXO
			if(lis[mid] > t[i]){
				r = mid - 1;
				ansj = mid;
			}
			else l = mid + 1;
		}
		if(ansj == -1){
			lis.push_back(t[i]);
		}
		else lis[ansj] = t[i];
	}
	return lis.size();
}
