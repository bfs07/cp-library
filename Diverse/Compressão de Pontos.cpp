map<int, int> rev;
for(int x : arr) {
	s1.insert(x);

vector<int> aux;
for(int x : s1) aux.pb(x);
for(int i=0; i<n; i++){
	int id = lower_bound(aux.begin(), aux.end(), arr[i]) - aux.begin();
	rev[id] = arr[i]; 
	arr[i] = id;
}