// OBS: Suffix Array build code imported from:
// https://github.com/gabrielpessoa1/Biblioteca-Maratona/blob/master/code/String/SuffixArray.cpp
// Because it's faster.

/// It is indexed by 0.
/// Let the given string be "banana".
///
/// 0 banana                          5 a
/// 1 anana     Sort the Suffixes     3 ana
/// 2 nana      ---------------->     1 anana
/// 3 ana        alphabetically       0 banana
/// 4 na                              4 na
/// 5 a                               2 nana
/// So the suffix array for "banana" is {5, 3, 1, 0, 4, 2}
///
/// LCP
///
/// 1 a
/// 3 ana
/// 0 anana
/// 0 banana
/// 2 na
/// 0 nana (The last position will always be zero)
///
/// So the LCP for "banana" is {1, 3, 0, 0, 2, 0}
///
class Suffix_Array {
private:
  string s;
  int n;

  typedef pair<int, int> Rank;

public:
  Suffix_Array(string &s) {
    this->n = s.size();
    this->s = s;
    // little optimization, remove the line above
    // this->s.swap(s);

    this->sa = build_suffix_array();
    this->lcp = build_lcp();
  }

private:
  /// Builds the Suffix Array for the string s.
  ///
  /// Time Complexity: O(n*log(n))
  /// Space Complexity: O(n)
  vector<int> build_suffix_array() {
    int n = this->s.size(), c = 0;
    vector<int> temp(n), posBucket(n), bucket(n), bpos(n), out(n);
    for (int i = 0; i < n; i++)
      out[i] = i;
    sort(out.begin(), out.end(),
         [&](int a, int b) { return this->s[a] < this->s[b]; });
    for (int i = 0; i < n; i++) {
      bucket[i] = c;
      if (i + 1 == n || this->s[out[i]] != this->s[out[i + 1]])
        c++;
    }
    for (int h = 1; h < n && c < n; h <<= 1) {
      for (int i = 0; i < n; i++)
        posBucket[out[i]] = bucket[i];
      for (int i = n - 1; i >= 0; i--)
        bpos[bucket[i]] = i;
      for (int i = 0; i < n; i++) {
        if (out[i] >= n - h)
          temp[bpos[bucket[i]]++] = out[i];
      }
      for (int i = 0; i < n; i++) {
        if (out[i] >= h)
          temp[bpos[posBucket[out[i] - h]]++] = out[i] - h;
      }
      c = 0;
      for (int i = 0; i + 1 < n; i++) {
        int a = (bucket[i] != bucket[i + 1]) || (temp[i] >= n - h) ||
                (posBucket[temp[i + 1] + h] != posBucket[temp[i] + h]);
        bucket[i] = c;
        c += a;
      }
      bucket[n - 1] = c++;
      temp.swap(out);
    }
    return out;
  }

  /// Builds the lcp (Longest Common Prefix) array for the string s.
  /// A value lcp[i] indicates length of the longest common prefix of the
  /// suffixes indexed by i and i + 1. Implementation of the Kasai’s Algorithm.
  ///
  /// Time Complexity: O(n)
  /// Space Complexity: O(n)
  vector<int> build_lcp() {
    lcp.resize(n, 0);
    vector<int> inverse_suffix(this->n);

    for (int i = 0; i < this->n; i++)
      inverse_suffix[sa[i]] = i;

    int k = 0;

    for (int i = 0; i < this->n; i++) {
      if (inverse_suffix[i] == this->n - 1) {
        k = 0;
        continue;
      }

      int j = sa[inverse_suffix[i] + 1];

      while (i + k < this->n && j + k < this->n && s[i + k] == s[j + k])
        k++;

      lcp[inverse_suffix[i]] = k;

      if (k > 0)
        k--;
    }

    return lcp;
  }

public:
  vector<int> sa;
  vector<int> lcp;

  /// LCS of two strings A and B.
  ///
  /// The string s must be initialized in the constructor as the string (A + '$'
  /// + B).
  ///
  /// The string A starts at index 1 and ends at index (separator - 1).
  /// The string B starts at index (separator + 1) and ends at the end of the
  /// string.
  ///
  /// Time Complexity: O(n)
  /// Space Complexity: O(1)
  int lcs(int separator) {
    assert(!isalpha(this->s[separator] && !isdigit(this->s[separator])));

    int ans = 0;

    for (int i = 0; i + 1 < this->sa.size(); i++) {
      int left = this->sa[i];
      int right = this->sa[i + 1];

      if ((left < separator && right > separator) ||
          (left > separator && right < separator))
        ans = max(ans, lcp[i]);
    }

    return ans;
  }
};