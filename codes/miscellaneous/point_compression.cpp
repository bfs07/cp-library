// map<int, int> rev;

/// Compress points in the array arr to the range [0..n-1].
///
/// Time Complexity: O(n log n)
vector<int> compress(vector<int> &arr) {
  vector<int> aux = arr;
  sort(aux.begin(), aux.end());
  aux.resize(unique(aux.begin(), aux.end()) - aux.begin());

  for (size_t i = 0; i < arr.size(); i++) {
    int id = lower_bound(aux.begin(), aux.end(), arr[i]) - aux.begin();
    // rev[id] = arr[i];
    arr[i] = id;
  }
  return arr;
}