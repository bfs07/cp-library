// What is Z Array?
// For a string str[0..n-1], Z array is of same length as string.
// An element Z[i] of Z array stores length of the longest substring
// starting from str[i] which is also a prefix of str[0..n-1]. The
// first entry of Z array is meaning less as complete string is always
// prefix of itself.
// Example:
// Index
// 0   1   2   3   4   5   6   7   8   9  10  11
// Text
// a   a   b   c   a   a   b   x   a   a   a   z
// Z values
// X   1   0   0   3   1   0   0   2   2   1   0
// More Examples:
// str  = "aaaaaa"
// Z[]  = {x, 5, 4, 3, 2, 1}

// str = "aabaacd"
// Z[] = {x, 1, 0, 2, 1, 0, 0}

// str = "abababab"
// Z[] = {x, 0, 6, 0, 4, 0, 2, 0}

vector<int> z_function(const string &s) {
  vector<int> z(s.size());
  int l = -1, r = -1;
  for (int i = 1; i < s.size(); ++i) {
    z[i] = i >= r ? 0 : min(r - i, z[i - l]);
    while (i + z[i] < s.size() && s[i + z[i]] == s[z[i]])
      z[i]++;
    if (i + z[i] > r)
      l = i, r = i + z[i];
  }
  return z;
}