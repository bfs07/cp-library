// https://medium.com/hackernoon/manachers-algorithm-explained-longest-palindromic-substring-22cb27a5e96f

/// Create a string containing '#' characters between any two characters.
string get_modified_string(string &s){
  string ret;
  for(int i = 0; i < s.size(); i++){
    ret.push_back('#');
    ret.push_back(s[i]);
  }
  ret.push_back('#');
  return ret;
}

/// Returns the first occurence of the longest palindrome based on the lps array.
///
/// Time Complexity: O(n)
string get_best(const int max_len, const string &str, const vector<int> &lps) {
  for(int i = 0; i < lps.size(); i++) {
    if(lps[i] == max_len) {
      string ans;
      int cnt = max_len / 2;
      int io = i - 1;
      while(cnt) {
        if(str[io] != '#') {
          ans += str[io];
          cnt--;
        }
        io--;
      }
      reverse(ans.begin(), ans.end());
      if(str[i] != '#')
        ans += str[i];
      cnt = max_len / 2;
      io = i + 1;
      while(cnt) {
        if(str[io] != '#') {
          ans += str[io];
          cnt--;
        }
        io++;
      }
      return ans;
    }
  }
}

/// Returns a pair containing the size of the longest palindrome and the first occurence of it.
///
/// Time Complexity: O(n)
pair<int, string> manacher(string &s) {
  int n = s.size();
  string str = get_modified_string(s);
  int len = (2 * n) + 1;
  //the i-th index contains the longest palindromic substring with the i-th char as the center
  vector<int> lps(len);
  int c = 0; //stores the center of the longest palindromic substring until now
  int r = 0; //stores the right boundary of the longest palindromic substring until now
  int max_len = 0;
  for(int i = 0; i < len; i++) {
    //get mirror index of i
    int mirror = (2 * c) - i;
    
    //see if the mirror of i is expanding beyond the left boundary of current longest palindrome at center c
    //if it is, then take r - i as lps[i]
    //else take lps[mirror] as lps[i]
    if(i < r)
      lps[i] = min(r - i, lps[mirror]);
    
    //expand at i
    int a = i + (1 + lps[i]);
    int b = i - (1 + lps[i]);
    while(a < len && b >= 0 && str[a] == str[b]) {
      lps[i]++;
      a++;
      b--;
    }
    
    //check if the expanded palindrome at i is expanding beyond the right boundary of current longest palindrome at center c
    //if it is, the new center is i
    if(i + lps[i] > r) {
      c = i;
      r = i + lps[i];
        
      if(lps[i] > max_len) //update max_len
        max_len = lps[i];
    }
  }

  return make_pair(max_len, get_best(max_len, str, lps));
}