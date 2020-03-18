int calcFat(vector<int> fatores) {
	int x = fatores[1];
	auto lo = lower_bound(fatores.begin(),fatores.end(), x);
	auto up = upper_bound(fatores.begin(), fatores.end(), x);
	int fat = 1;
	while(up != fatores.end()) {
		fat *= (up-lo+1);
		lo = lower_bound(fatores.begin(), fatores.end(), *up);
		up = upper_bound(fatores.begin(), fatores.end(), *up);
	}
	fat *= (up-lo+1);
	return fat;
}
