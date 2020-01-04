/// Program to find the LCS between k different strings.
///
/// Time Complexity: O(n*log(n))
/// Space Complexity: O(n*log(n))
int main() {
  int n;

  cin >> n;

  vector<string> arr(n);

  int sum = 0;
  for(string &x: arr) {
    cin >> x;
    sum += x.size() + 1;
  }

  string concat;
  vector<int> ind(sum);
  int cnt = 0;
  for(string &x: arr) {
    if(concat.size())
      concat += (char)cnt;
    concat += x;
  }

  cnt = 0;
  for(int i = 0; i < concat.size(); i++) {
    ind[i] = cnt;
    if(concat[i] < 10)
      cnt++;
  }

  Suffix_Array say(concat);
  vector<int> sa = say.get_suffix_array();
  Sparse_Table spt(say.get_lcp());

  vector<int> freq(n);
  int cnt1 = 0;

  /// Ignore separators
  int i = n, j = n - 1;
  int ans = 0;

  while(true) {

    if(cnt1 == n) {

      ans = max(ans, spt.query(i, j - 1));

      int idx = ind[sa[i]];
      freq[idx]--;
      if(freq[idx] == 0)
        cnt1--;
      i++;
    } else if(j == (int)sa.size() - 1)
      break; 
    else {
      j++;
      int idx = ind[sa[j]];
      freq[idx]++;
      if(freq[idx] == 1)
        cnt1++;
    }
  }

  cout << ans << endl;
}