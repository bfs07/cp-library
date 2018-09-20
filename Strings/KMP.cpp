// (achar substring numa string)
// Complexidade: O(n)

// TXT = “ABABABABA”, PAT = “AB”
// Fills lps[] for given patttern pat[0..M-1]
void compute(string &pat, int m, int lps[]) {
  // length of the previous longest prefix suffix
  int len = 0;
  lps[0] = 0; // lps[0] is always 0
 
  // the loop calculates lps[i] for i = 1 to m-1
  int i = 1;
  while (i < m) {
    if (pat[i] == pat[len]) {
      len++, i++;
      lps[i] = len;
    } else {// (pat[i] != pat[len])
      if (len != 0)
        len = lps[len-1];
      else
        lps[i++] = 0;
    }
  }
}

// Driver program to test above function
// Prints occurrences of txt[] in pat[]
int KMPSearch(string pat, string txt) {
  int n = txt.size(), m = pat.size();
  // create lps[] that will hold the longest prefix suffix values for pattern
  int lps[m], c = 0;
 
  // Preprocess the pattern (calculate lps[] array)
  compute(pat, m, lps);
 
  int i = 0;  // index for txt[]
  int j = 0;  // index for pat[]
  while (i < n) {
    if (pat[j] == txt[i])
      j++, i++;
 
    if (j == m) {
      printf("pattern at %d \n", i-j);
      j = lps[j-1];
      c++;
      // Múltiplos matches
    }
 
    // mismatch after j matches
    else if (i < n && pat[j] != txt[i]){
      // Do not match lps[0..lps[j-1]] characters, they will match anyway
      if (j != 0)
        j = lps[j-1];
      else
        i = i+1;
    }
  }
  // return the number of occurrences
  return c;
}
int main() {
  string txt = "ABABDABACDABABCABAB";
  string pat = "AB";
  KMPSearch(pat, txt);
}
Output:
pattern at 0,2,5,10,12,15,17
