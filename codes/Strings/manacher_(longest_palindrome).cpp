// https://medium.com/hackernoon/manachers-algorithm-explained-longest-palindromic-substring-22cb27a5e96f

string get_modified_string(string &s){
  string ret;
  for(int i = 0; i < s.size(); i++){
    ret.push_back('#');
    ret.push_back(s[i]);
  }
  ret.push_back('#');
  return ret;
}

int manacher(string &s) {
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

  return max_len;
}
