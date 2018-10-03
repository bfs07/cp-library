map<int, int> rev;

void compress(vector<int> &arr) {

  set<int> s;

  for(int x : arr) 
    s.insert(x);

  vector<int> aux;
  for(int x : s) aux.pb(x);

  for(int i=0; i<arr.size(); i++){
    int id = lower_bound(aux.begin(), aux.end(), arr[i]) - aux.begin();
    // rev[id] = arr[i]; 
    arr[i] = id + 1;
  }

}